#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 64

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

	if (length == 0) {
		return NULL;
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

bignum_t* bignum_copy(const bignum_t* src) {
	bignum_t* dst = malloc(sizeof(bignum_t));

	dst->length = src->length;
	dst->string = calloc(src->length + 1, sizeof(char));
	strncpy((char*) dst->string, src->string, src->length);

	dst->is_negative = src->is_negative;

	dst->whole_digits = src->whole_digits;

	return dst;
}

char* bignum_to_string(const bignum_t* num) {
	char* str = calloc(get_true_length(num), sizeof(char));
	
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
