#include "../include/bignum.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
	const bignum_t* a = bignum_create_from_double(0.05);
	const bignum_t* b = bignum_create_from_double(0.05);

	const bignum_comparison_t cmpresult = bignum_compare(a, b);
	printf("a > b = %s\n", cmpresult == BIGNUM_GT ? "true" : "false");
	printf("a < b = %s\n", cmpresult == BIGNUM_LT ? "true" : "false");
	printf("a == b = %s\n", cmpresult == BIGNUM_EQ ? "true" : "false");

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

	bignum_t* result = bignum_add(a, b);
	char* resultstr = bignum_to_string(result);
	printf("result = %s\n", resultstr);
	free(resultstr);
	bignum_cleanup(result);

	bignum_cleanup(b);

berror:
	bignum_cleanup(a);

aerror:
	return 0;
}
