#include "../include/bignum.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
	const bignum_t* a = bignum_create_from_string("5");
	const bignum_t* b = bignum_create_from_string("12");

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

	bignum_t* sum = bignum_add(a, b);
	bignum_t* dif = bignum_subtract(a, b);

	char* sumstr = bignum_to_string(sum);
	char* difstr = bignum_to_string(dif);
	
	printf("a + b = %s\na - b = %s\n", sumstr, difstr);

	free(sumstr);
	free(difstr);

	bignum_cleanup(sum);
	bignum_cleanup(dif);

	bignum_cleanup(b);

berror:
	bignum_cleanup(a);

aerror:
	return 0;
}
