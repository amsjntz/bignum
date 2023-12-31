#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>

// treats a and b as always positive, will return a negative value if b > a
bignum_t* unsigned_subtract(const bignum_t* a, const bignum_t* b) {
	unsigned int newlen = MAX(get_true_length(a), get_true_length(b)) + 1;
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

// treats a and b as always positive, will always return positive value
bignum_t* unsigned_add(const bignum_t* a, const bignum_t* b) {
	unsigned int newlen = MAX(get_true_length(a), get_true_length(b)) + 2;
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

bignum_t* bignum_add(const bignum_t* a, const bignum_t* b) {
	bignum_t* result = NULL;
	if (a->is_negative && !b->is_negative) { // -n + m = m - n
		result = unsigned_subtract(b, a);
	} else if (!a->is_negative && b->is_negative) {
		result = unsigned_subtract(b, a);
		result->is_negative = true;
	}

	result = unsigned_add(a, b);

	if (a->is_negative && b->is_negative) {
		result->is_negative = true;
	}

	return result;
}

bignum_t* bignum_subtract(const bignum_t* a, const bignum_t* b) {
	return unsigned_subtract(a, b);
}
