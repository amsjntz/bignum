#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>
#include <stdbool.h>

#include "bignum_approximation.h"

// find result by approximation
bignum_t* unsigned_divide(const bignum_t* a, const bignum_t* b, unsigned int digits) {
	int upper_power = MAX(2, MAX(get_maximal_power(a) - get_minimal_power(b), // TODO: fix this mess
			get_maximal_power(b) - get_minimal_power(a)));
	bignum_t* upper = bignum_create_by_power(upper_power);
	bignum_t* lower = bignum_create_from_string("0");
	bignum_approx_t approx = approx_initialize(lower, upper, digits);

	while (!approx_precise_enough(&approx)) {
		bignum_t* guess = approx_create_next_guess(&approx);

		// check direction from guess to result
		bignum_t* check = bignum_multiply(guess, b);
		bignum_comparison_t direction = bignum_unsigned_compare(a, check);
		bignum_cleanup(check);

		approx_adjust_bounds(&approx, guess, direction);
	}

	return approx_finalize(&approx);
}

bignum_t* bignum_divide(const bignum_t* a, const bignum_t* b, unsigned int digits) {
	if (is_zero(b)) return NULL;

	bignum_t* result = unsigned_divide(a, b, digits);

	if ((a->is_negative ^ b->is_negative) == 1) {
		result->is_negative = true;
	}

	return result;
}
