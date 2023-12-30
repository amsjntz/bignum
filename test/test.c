#include "../include/bignum.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
	const bignum_t* a = bignum_create_from_double(110.5);
	const bignum_t* b = bignum_create_from_double(195.5051);

	if (a == NULL) {
		printf("a is not a number\n");
		goto aerror;
	}

	char* astr = bignum_to_string(a);
	printf("a = %s\n", astr);
	free(astr);

	if (b == NULL) {
		printf("b is not a number\n");
		goto berror;
	}

	char* bstr = bignum_to_string(b);
	printf("b = %s\n", bstr);
	free(bstr);

	bignum_t* sum = bignum_add(a, b);
	char* sumstr = bignum_to_string(sum);
	printf("sum = %s\n", sumstr);
	free(sumstr);
	bignum_cleanup(sum);

	bignum_cleanup(b);

berror:
	bignum_cleanup(a);

aerror:
	return 0;
}
