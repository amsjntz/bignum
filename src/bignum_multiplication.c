#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	unsigned char value;
	int power;
} powered_number;

unsigned int create_result_string(char target[], unsigned int len, int aminpow, int bminpow) {
	memset(target, '0', len);
	target[len - 1] = '\0';
	if (aminpow < 0 || bminpow < 0) {
		unsigned int commapos = len - 2 - ABS(aminpow) - ABS(bminpow);
		target[commapos] = '.';
		return commapos;
	}
	return len - 1;
}

// returns the carry
unsigned char add_at_power(char target[], int power, unsigned char value, unsigned int commapos) {
	unsigned int bufferpos = commapos - power;
	if (power >= 0) bufferpos--;
	unsigned char a = target[bufferpos] - '0';
	unsigned char sum = a + value;
	target[bufferpos] = '0' + (sum % 10);
	return sum / 10;
}

bignum_t* bignum_multiply(const bignum_t* a, const bignum_t* b) {
	int amaxpow = get_maximal_power(a);
	int aminpow = get_minimal_power(a);

	int bmaxpow = get_maximal_power(b);
	int bminpow = get_minimal_power(b);

	
	unsigned int num_idx = 0;
	powered_number numbers[get_true_length(a) * get_true_length(b)];

	for (int bpower = bmaxpow; bpower >= bminpow; bpower--) {
		for (int apower = aminpow; apower <= amaxpow; apower++) {
			unsigned int product = get_digit_at(a, apower) * get_digit_at(b, bpower);
			numbers[num_idx++] = (powered_number) {
				.value = product,
				.power = apower + bpower
			};
		}
	}

	unsigned int result_length = get_true_length(a) + get_true_length(b);
	char result[result_length];
	unsigned int commapos = create_result_string(result, result_length, aminpow, bminpow);

	for (unsigned int i = 0; i < num_idx; i++) {
		unsigned int power = numbers[i].power;
		unsigned char carry = add_at_power(result, power, numbers[i].value, commapos);
		while (carry > 0) {
			carry = add_at_power(result, ++power, carry, commapos);
		}
	}

	return bignum_create_from_string(result);
}
