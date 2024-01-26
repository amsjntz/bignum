#include "../include/bignum.h"

#include <stdbool.h>

const bignum_t* BIGNUM_ZERO = &(bignum_t) {
	.string = "0",
	.length = 1,
	.is_negative = false,
	.whole_digits = 1
};

const bignum_t* BIGNUM_ONE = &(bignum_t) {
	.string = "1",
	.length = 1,
	.is_negative = false,
	.whole_digits = 1
};

const bignum_t* BIGNUM_HALF = &(bignum_t) {
	.string = "0.5",
	.length = 3,
	.is_negative = false,
	.whole_digits = 1
};
