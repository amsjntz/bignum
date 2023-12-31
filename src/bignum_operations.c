#include "../include/bignum.h"
#include "bignum_helpers.h"

bignum_t* bignum_add(const bignum_t* a, const bignum_t* b) {
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
