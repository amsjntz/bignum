#include "../include/bignum.h"
#include "bignum_helpers.h"

// ignores is_negative of both numbers
bignum_comparison_t bignum_unsigned_compare(const bignum_t* a, const bignum_t* b) {
	int minpower = MIN(get_minimal_power(a), get_minimal_power(b));
	int maxpower = MAX(get_maximal_power(a), get_maximal_power(b));

	for (int power = maxpower; power >= minpower; power--) {
		unsigned short adigit = get_digit_at(a, power);
		unsigned short bdigit = get_digit_at(b, power);
		if (adigit == bdigit) continue;

		if (adigit > bdigit) return BIGNUM_GT;
		if (adigit < bdigit) return BIGNUM_LT;
	}

	return BIGNUM_EQ;
}

bignum_comparison_t bignum_compare(const bignum_t* a, const bignum_t* b) {
	if (a->is_negative && !b->is_negative) { // a < 0 and b > 0 => a < b
		return BIGNUM_LT;
	} else if (!a->is_negative && b->is_negative) { // a > 0 and b < 0 => a > b
		return BIGNUM_GT;
	} else if (a->is_negative && b->is_negative) { // a < 0 and b < 0
		return bignum_unsigned_compare(b, a);
	}
	return bignum_unsigned_compare(a, b);
}
