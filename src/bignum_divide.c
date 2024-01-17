#include "../include/bignum.h"
#include "bignum_helpers.h"

// this works on the assumption that when a / b = result, b * result = a.
// it basically brute forces its way to the result by starting at 5 for every digit,
// and then adjusting it until we got closer to the correct result.
// very memory intensive and slow. FIXME
bignum_t* unsigned_divide(const bignum_t* a, const bignum_t* b, unsigned int digits) {
	bignum_t* result = bignum_create_from_string("5");
	bignum_t* nudge = bignum_create_from_string("1");
	bignum_t* nudgefactor = bignum_create_from_string("0.1");

	unsigned int generated_digits = 0;

	do {
		bignum_comparison_t lastcomp = BIGNUM_LT;
		while (true) {
			bignum_t* check = bignum_multiply(result, b);
			bignum_comparison_t comp = bignum_unsigned_compare(check, a);
			bignum_cleanup(check);

			// last tried digit was too small, new one is too big 
			// -> result must be in between, so the previous attempt was correct
			if (lastcomp == BIGNUM_GT && comp == BIGNUM_LT) {
				break;
			}

			bignum_t* newres;
			switch (comp) {
				case BIGNUM_EQ:
					goto exit; // result * b = a -> we can exit early!
				case BIGNUM_LT:
					// result * b < a -> result too small
					newres = bignum_add(result, nudge);
					break;
				case BIGNUM_GT:
					// result * b > a -> result too big
					newres = bignum_subtract(result, nudge); 
					break;
			}
			bignum_cleanup(result);
			result = newres;

			lastcomp = comp;
		}

		bignum_t* newnudge = bignum_multiply(nudge, nudgefactor);
		bignum_cleanup(nudge);
		nudge = newnudge;

		if (get_minimal_power(result) < 0) {
			generated_digits++;
		}

	} while (generated_digits < digits);

exit:
	bignum_cleanup(nudge);
	bignum_cleanup(nudgefactor);
	return result;
}

bignum_t* bignum_divide(const bignum_t* a, const bignum_t* b, unsigned int digits) {
	bignum_t* result = unsigned_divide(a, b, digits);

	if ((a->is_negative ^ b->is_negative) == 1) {
		result->is_negative = true;
	}

	return result;
}
