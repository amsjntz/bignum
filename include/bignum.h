#include <stdbool.h>

// TODO: add proper documentation

typedef struct {
	const char* number_string;
	unsigned int length;

	bool is_negative;

	unsigned int whole_digits;
} bignum_t;

bignum_t* bignum_create_from_string(const char* src);
bignum_t* bignum_create_from_int(int value);
bignum_t* bignum_create_from_double(double value);

bignum_t* bignum_add(const bignum_t* a, const bignum_t* b); // returns a + b
bignum_t* bignum_subtract(const bignum_t* a, const bignum_t* b); // returns a - b
bignum_t* bignum_multiply(const bignum_t* a, const bignum_t* b); // returns a * b
bignum_t* bignum_divide(const bignum_t* a, const bignum_t* b); // returns a / b
