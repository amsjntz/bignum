#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdbool.h>

bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

bool is_valid_char(char c) {
	return is_digit(c) || c == '.';
}

bool has_floating_point(const bignum_t* num) {
	return num->length != num->whole_digits;
}

unsigned int get_true_length(const bignum_t* num) {
	return (num->is_negative ? 1 : 0) + num->length + 1;
}

unsigned short get_digit_at(const bignum_t* num, int power) {
	int idx;
	if (power >= 0) {
		idx = num->whole_digits - power - 1;
	} else {
		idx = num->whole_digits - power;
	}
	if (idx < 0 || idx >= (int) num->length) {
		return 0;
	}
	return num->string[idx] - '0';
}

int get_minimal_power(const bignum_t* num) {
	if (!has_floating_point(num)) {
		return 0;
	}
	return num->whole_digits - num->length + 1;
}

int get_maximal_power(const bignum_t* num) {
	int minpow = get_minimal_power(num);
	for (int power = num->whole_digits - 1; power >= minpow; power--) {
		if (get_digit_at(num, power) != 0) {
			return power;
		}
	}
	return 0;
}

bool is_zero(const bignum_t* num) {
	return get_maximal_power(num) == get_minimal_power(num) &&
		num->string[0] == '0';
}
