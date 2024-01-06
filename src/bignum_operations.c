#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>

// treats a and b as always positive, will always return a positive value
bignum_t* unsigned_add(const bignum_t* a, const bignum_t* b) {
	unsigned int newlen = get_true_length(a) + get_true_length(b);
	char buffer[newlen];
	buffer[newlen - 1] = '\0';
	
	unsigned int carry = 0;
	int power = MIN(get_minimal_power(a), get_minimal_power(b));
	for (int pos = newlen - 2; pos >= 0; pos--) {
		if (power == 0) {
			buffer[pos] = '.';
			pos--;
		}

		unsigned int sum = get_digit_at(a, power) + get_digit_at(b, power) + carry;
		if (sum >= 10) {
			carry = 1;
			sum -= 10;
		} else {
			carry = 0;
		}
		buffer[pos] = '0' + sum;

		power++;
	}

	return bignum_create_from_string(buffer);
}

// treats a and b as always positive, will return negative value if |b| > |a|
bignum_t* unsigned_subtract(const bignum_t* a, const bignum_t* b) {
	if (bignum_unsigned_compare(b, a) == BIGNUM_GT) { // b > a
		bignum_t* result = unsigned_subtract(b, a);
		result->is_negative = true;
		return result;
	}

	unsigned int newlen = get_true_length(a) + get_true_length(b);
	char buffer[newlen];
	buffer[newlen - 1] = '\0';

	unsigned int carry = 0;
	int power = MIN(get_minimal_power(a), get_minimal_power(b));
	for (int pos = newlen - 2; pos >= 0; pos--) {
		if (power == 0) {
			buffer[pos] = '.';
			pos--;
		}

		int diff = get_digit_at(a, power) - get_digit_at(b, power) - carry;
		if (diff < 0) {
			carry = 1;
			diff += 10;
		} else {
			carry = 0;
		}
		buffer[pos] = '0' + diff;

		power++;
	}

	return bignum_create_from_string(buffer);
}

bignum_t* bignum_add(const bignum_t* a, const bignum_t* b) {
	if (a->is_negative && b->is_negative) { // a < 0 and b < 0 => a + b = -(|a| + |b|)
		bignum_t* result = unsigned_add(a, b);
		result->is_negative = true;
		return result;
	} else if (a->is_negative && !b->is_negative) { // a < 0 and b > 0 => a + b = b - |a|
		return unsigned_subtract(b, a);
	} else if (!a->is_negative && b->is_negative) { // a > 0 and b < 0 => a + b = a - |b|
		return unsigned_subtract(a, b);
	}
	// only remaining case: a > 0 and b > 0 => normal addition
	return unsigned_add(a, b);
}

bignum_t* bignum_subtract(const bignum_t* a, const bignum_t* b) {
	if (a->is_negative && b->is_negative) { // a < 0 and b < 0 => a - b = |b| - |a|
		return unsigned_subtract(b, a);
	} else if (a->is_negative && !b->is_negative) { // a < 0 and b > 0 => a - b = -(|a| + b)
		bignum_t* result = unsigned_add(a, b);
		result->is_negative = true;
		return result;
	} else if (!a->is_negative && b->is_negative) { // a > 0 and b < 0 => a - b = a + |b|
		return unsigned_add(a, b);
	}
	// only remaining case: a > 0 and b > 0 => normal subtraction
	return unsigned_subtract(a, b);
}

bignum_t* bignum_multiply(const bignum_t* a, const bignum_t* b) {
	int amaxpow = get_maximal_power(a);
	int aminpow = get_minimal_power(a);

	int bmaxpow = get_maximal_power(b);
	int bminpow = get_minimal_power(b);


	for (int bpower = bmaxpow; bpower >= bminpow; bpower--) {
		for (int apower = aminpow; apower < amaxpow; apower++) {
			unsigned int product = get_digit_at(a, apower) * get_digit_at(b, bpower);
		}
	}
	return bignum_create_from_string("0");
}
