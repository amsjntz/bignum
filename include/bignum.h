#pragma once

#include <stdbool.h>

// TODO: add proper documentation

typedef struct {
	const char* string;
	unsigned int length; // length without null-termination

	bool is_negative;

	unsigned int whole_digits;
} bignum_t;

extern const bignum_t* BIGNUM_ZERO;
extern const bignum_t* BIGNUM_ONE;
extern const bignum_t* BIGNUM_HALF;

bignum_t* bignum_create_from_string(const char* src);
bignum_t* bignum_create_from_int(int value);
bignum_t* bignum_create_from_double(double value);

bignum_t* bignum_copy(const bignum_t* src);

char* bignum_to_string(const bignum_t* num);

bignum_t* bignum_add(const bignum_t* a, const bignum_t* b); // returns a + b
bignum_t* bignum_subtract(const bignum_t* a, const bignum_t* b); // returns a - b
bignum_t* bignum_multiply(const bignum_t* a, const bignum_t* b); // returns a * b
bignum_t* bignum_divide(const bignum_t* a, const bignum_t* b, unsigned int digits); // returns a / b

typedef enum {BIGNUM_EQ, BIGNUM_LT, BIGNUM_GT} bignum_comparison_t;

bignum_comparison_t bignum_compare(const bignum_t* a, const bignum_t* b);
bignum_comparison_t bignum_unsigned_compare(const bignum_t* a, const bignum_t* b);

void bignum_limit_precision(bignum_t* num, unsigned int precision);

void bignum_cleanup(const bignum_t* num);
