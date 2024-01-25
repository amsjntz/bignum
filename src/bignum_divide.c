#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	bignum_t* lower;
	bignum_t* upper;
} narrowed_result_t;

typedef struct {
	const bignum_t* a;
	const bignum_t* b;
	const bignum_t* max_difference;
} bignum_division_t;

bool precise_enough(narrowed_result_t* result, const bignum_t* max_difference) {
	if (result->lower->whole_digits != result->upper->whole_digits) {
		return false;
	}

	bignum_t* difference = bignum_subtract(result->lower, result->upper);
	bignum_comparison_t cmp = bignum_unsigned_compare(difference, max_difference);
	bignum_cleanup(difference);
	return cmp != BIGNUM_GT;
}

void narrow_iterative(narrowed_result_t* bounds, bignum_division_t* division) {
	bignum_t* half_factor = bignum_create_from_string("0.5");

	while (!precise_enough(bounds, division->max_difference)) {
		bignum_t* sum = bignum_add(bounds->lower, bounds->upper);
		bignum_t* center = bignum_multiply(sum, half_factor);
		bignum_cleanup(sum);

		bignum_t* check = bignum_multiply(center, division->b);
		bignum_comparison_t comparison = bignum_unsigned_compare(check, division->a);
		bignum_cleanup(check);

		if (comparison == BIGNUM_LT) {
			bignum_cleanup(bounds->lower);
			bounds->lower = center;
		} else {
			bignum_cleanup(bounds->upper);
			bounds->upper = center;
			// center contains correct result -> exit loop
			if (comparison == BIGNUM_EQ) {
				break;
			}
		}
	}

	bignum_cleanup(half_factor);
}

// returns pow(10, power)
bignum_t* create_bignum_by_power(int power) {
	if (power >= 0) {
		char str[power + 2];
		for (int i = 1; i < power + 1; i++) {
			str[i] = '0';
		}
		str[0] = '1';
		str[power + 1] = '\0';
		return bignum_create_from_string(str);
	} else {
		char str[-power + 3];
		for (int i = 0; i < -power + 1; i++) {
			str[i] = '0';
		}
		str[1] = '.';
		str[-power + 1] = '1';
		str[-power + 2] = '\0';
		return bignum_create_from_string(str);
	}
}

bignum_t* unsigned_divide(const bignum_t* a, const bignum_t* b, unsigned int digits) {
	narrowed_result_t bounds;
	int upper_power = MAX(1, MAX(get_maximal_power(a) - get_minimal_power(b),
			get_maximal_power(b) - get_minimal_power(a)));
	bounds.upper = create_bignum_by_power(upper_power);
	bounds.lower = bignum_create_from_string("0");

	bignum_division_t division;
	division.a = a;
	division.b = b;

	division.max_difference = create_bignum_by_power(-((int) digits));

	narrow_iterative(&bounds, &division);

	bignum_cleanup(division.max_difference);

	bignum_cleanup(bounds.lower);

	crop_to_precision(bounds.upper, digits);
	return bounds.upper;
}

bignum_t* bignum_divide(const bignum_t* a, const bignum_t* b, unsigned int digits) {
	if (is_zero(b)) return NULL;

	bignum_t* result = unsigned_divide(a, b, digits);

	if ((a->is_negative ^ b->is_negative) == 1) {
		result->is_negative = true;
	}

	return result;
}
