#include "bignum_approximation.h"
#include "bignum_helpers.h"

bignum_approx_t approx_initialize(bignum_t* lower, bignum_t* upper,
		unsigned int precision) {
	return (bignum_approx_t) {
		.lower = lower,
		.upper = upper,
		.precision = precision,
		.max_difference = bignum_create_by_power(-((int) precision))
	};
}

bool approx_precise_enough(bignum_approx_t* approx) {
	if (approx->upper->whole_digits != approx->lower->whole_digits) {
		return false;
	}

	bignum_t* difference = bignum_subtract(approx->upper, approx->lower);
	bignum_comparison_t cmp = bignum_unsigned_compare(difference,
			approx->max_difference);
	bignum_cleanup(difference);
	return cmp != BIGNUM_GT;
}

bignum_t* approx_create_next_guess(bignum_approx_t* approx) {
	bignum_t* sum = bignum_add(approx->lower, approx->upper);
	bignum_t* center = bignum_multiply(sum, BIGNUM_HALF);
	bignum_cleanup(sum);
	return center;
}

void approx_adjust_bounds(bignum_approx_t* approx, bignum_t* guess,
		bignum_comparison_t direction) {
	if (direction == BIGNUM_LT) {
		bignum_cleanup(approx->upper);
		approx->upper = guess;
	} else {
		bignum_cleanup(approx->lower);
		approx->lower = guess;
	}
}

bignum_t* approx_finalize(bignum_approx_t* approx) {
	bignum_cleanup(approx->max_difference);
	bignum_cleanup(approx->lower);

	crop_to_precision(approx->upper, approx->precision);
	return approx->upper;
}
