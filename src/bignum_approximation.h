#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	bignum_t* lower;
	bignum_t* upper;

	unsigned int precision;
	bignum_t* max_difference;
} bignum_approx_t;

// I made the decision to not have this be allocated on the heap.
// After all, the struct is not that large and this function will
// not be called too often. The performance difference is probably
// negligable anyways.
// ALWAYS use fresh bignums as lower/upper, as in freshly created
// or copied. Otherwise they might get cleaned up unexpectedly!
bignum_approx_t approx_initialize(bignum_t* lower, bignum_t* upper,
		unsigned int precision);

// checks if difference between bounds is <= max_difference
bool approx_precise_enough(bignum_approx_t* approx);

bignum_t* approx_create_next_guess(bignum_approx_t* approx);

// if direction is BIGNUM_LT, the result will be between lower and guess.
// if it is BIGNUM_GT, result will be between guess and upper
void approx_adjust_bounds(bignum_approx_t* approx, bignum_t* guess,
		bignum_comparison_t direction);

// returns the final approximation and cleans up.
// does not free the approx pointer, as it's supposed to be on the stack.
// see comment further up.
bignum_t* approx_finalize(bignum_approx_t* approx);
