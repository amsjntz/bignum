#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
	return num->length == 1 && num->string[0] == '0';
}

void remove_trailing_digits(bignum_t* num) {
	unsigned int left = 0;
	unsigned int right = num->length - 1;

	bool has_point = has_floating_point(num);
	
	while (true) {
		bool adjusted = false;
		if (num->string[left] == '0') {
			left++;
			adjusted = true;
		}
		if (has_point && num->string[right] == '0') {
			right--;
			adjusted = true;
		}

		if (!adjusted) {
			break;
		}
	}
	
	unsigned int newlen = right - left + 1;
	if (num->string[right] == '.') {
		newlen--;
	}
	if (newlen == 0) {
		newlen = 1;
		left--;
	}
	if (num->string[left] == '.') {
		newlen++;
		left--;
	}

	char* newstr = calloc(newlen + 1, sizeof(char));
	strncpy((char*) newstr, num->string+left, newlen);

	free((char*) num->string);
	num->string = newstr;

	num->length = newlen;
	num->whole_digits -= left;
}

void bignum_limit_precision(bignum_t* num, unsigned int precision) {
	if (!has_floating_point(num) || get_minimal_power(num) > -((int) precision)) {
		return;
	}

	unsigned int new_length = MIN(num->length + 1, num->whole_digits + precision + 2);
	char* newstring = calloc(new_length, sizeof(char));

	unsigned int index = 0;
	while (num->string[index] != '\0' && index < new_length - 1) {
		newstring[index] = num->string[index];
		index++;
	}

	free((char*) num->string);
	num->string = newstring;
	num->length = new_length - 1;

	remove_trailing_digits(num);
}

// returns pow(10, power)
bignum_t* bignum_create_by_power(int power) {
	if (power >= 0) {
		char str[power + 2];
		for (int i = 1; i < power + 1; i++) {
			str[i] = '0';
		}
		str[0] = '1';
		str[power + 1] = '\0';
		return bignum_create_from_string(str);
	} else {
		char str[-power + 3];
		for (int i = 0; i < -power + 1; i++) {
			str[i] = '0';
		}
		str[1] = '.';
		str[-power + 1] = '1';
		str[-power + 2] = '\0';
		return bignum_create_from_string(str);
	}
}
