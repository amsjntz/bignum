#include "../include/bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_char(char c) {
	return (c >= '0' && c <= '9') || c == '.';
}

bignum_t* bignum_create_from_string(const char* src) {
	unsigned int length = 0;
	bool is_negative = false;
	int whole_digits = -1;

	if (src[0] == '-') {
		src++;
		is_negative = true;
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

	bignum_t* number = malloc(sizeof(bignum_t));

	number->number_string = calloc(length + 1, sizeof(char));
	strncpy((char*) number->number_string, src, length);

	number->length = length;
	number->is_negative = is_negative;
	number->whole_digits = whole_digits;

	printf("%s\n", number->number_string);

	return number;
}
