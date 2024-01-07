#include "../include/bignum.h"
#include "bignum_helpers.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bignum_t* bignum_multiply(const bignum_t* a, const bignum_t* b) {
	int amaxpow = get_maximal_power(a);
	int aminpow = get_minimal_power(a);

	int bmaxpow = get_maximal_power(b);
	int bminpow = get_minimal_power(b);

	struct powered_number {
		unsigned int value;
		int power;
	};

	unsigned int num_idx = 0;
	struct powered_number numbers[get_true_length(a) * get_true_length(b)];

	for (int bpower = bmaxpow; bpower >= bminpow; bpower--) {
		for (int apower = aminpow; apower <= amaxpow; apower++) {
			unsigned int product = get_digit_at(a, apower) * get_digit_at(b, bpower);
			numbers[num_idx++] = (struct powered_number) {
				.value = product,
				.power = apower + bpower
			};
		}
	}

	unsigned int result_length = get_true_length(a) + get_true_length(b);
	char result[result_length];
	memset(result, '0', result_length);
	result[result_length - 1] = '\0';
	int minpow = MIN(aminpow, bminpow);
	if (minpow < 0) {
		result[result_length - 2 + minpow] = '.';
	}

	printf("%s\n", result);

	return bignum_create_from_string("0");
}
