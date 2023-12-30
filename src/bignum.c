#include "../include/bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 64

bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

bool is_valid_char(char c) {
	return is_digit(c) || c == '.';
}

void remove_trailing_digits(bignum_t* num) {
	unsigned int left = 0;
	unsigned int right = num->length - 1;

	bool has_floating_point = num->length != num->whole_digits;
	
	while (true) {
		bool adjusted = false;
		if (num->string[left] == '0') {
			left++;
			adjusted = true;
		}
		if (has_floating_point && num->string[right] == '0') {
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

bignum_t* bignum_create_from_string(const char* src) {
	unsigned int length = 0;
	bool is_negative = false;
	int whole_digits = -1;

	if (src[0] == '-') {
		src++;
		is_negative = true;
	}
	if (!is_digit(src[0])) {
		return NULL;
	}

	for (unsigned int i = 0; src[i] != '\0'; i++) {
		if (!is_valid_char(src[i])) {
			return NULL;
		}

		if (src[i] == '.') {
			if (whole_digits == -1) {
				whole_digits = length;
			} else {
				return NULL;
			}
		}

		length++;
	}

	if (whole_digits == -1) {
		whole_digits = length;
	}

	bignum_t* number = malloc(sizeof(bignum_t));

	number->string = calloc(length + 1, sizeof(char));
	strncpy((char*) number->string, src, length);

	number->length = length;
	number->is_negative = is_negative;
	number->whole_digits = whole_digits;

	remove_trailing_digits(number);
	return number;
}

bignum_t* bignum_create_from_int(int value) {
	char buffer[BUFFER_LENGTH];
	if (snprintf(buffer, BUFFER_LENGTH, "%d", value) >= BUFFER_LENGTH) {
		return NULL;
	}
	return bignum_create_from_string(buffer);
}

bignum_t* bignum_create_from_double(double value) {
	char buffer[BUFFER_LENGTH];
	if (snprintf(buffer, BUFFER_LENGTH, "%f", value) >= BUFFER_LENGTH) {
		return NULL;
	}
	return bignum_create_from_string(buffer);
}

char* bignum_to_string(const bignum_t* num) {
	unsigned int truelength = (num->is_negative ? 1 : 0) + num->length + 1;

	char* str = calloc(truelength, sizeof(char));
	
	unsigned int offset = 0;
	if (num->is_negative) {
		str[0] = '-';
		offset++;
	}
	
	strncpy(str + offset, num->string, num->length);

	return str;
}

void bignum_cleanup(const bignum_t* num) {
	free((void*) num->string);
	free((void*) num);
}
