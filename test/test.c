#include "../include/bignum.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
	const bignum_t* a = bignum_create_from_string("1");
	const bignum_t* b = bignum_create_from_string("4");

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

	const bignum_comparison_t cmpresult = bignum_compare(a, b);
	printf("a > b = %s\n", cmpresult == BIGNUM_GT ? "true" : "false");
	printf("a < b = %s\n", cmpresult == BIGNUM_LT ? "true" : "false");
	printf("a == b = %s\n", cmpresult == BIGNUM_EQ ? "true" : "false");

	bignum_t* sum = bignum_add(a, b);
	bignum_t* dif = bignum_subtract(a, b);
	bignum_t* prd = bignum_multiply(a, b);
	bignum_t* div = bignum_divide(a, b, 11);

	char* sumstr = bignum_to_string(sum);
	char* difstr = bignum_to_string(dif);
	char* prdstr = bignum_to_string(prd);
	char* divstr = bignum_to_string(div);
	
	printf("a + b = %s\n", sumstr);
	printf("a - b = %s\n", difstr);
	printf("a * b = %s\n", prdstr);
	printf("a / b = %s\n", divstr);

	free(sumstr);
	free(difstr);
	free(prdstr);
	free(divstr);

	bignum_cleanup(sum);
	bignum_cleanup(dif);
	bignum_cleanup(prd);
	bignum_cleanup(div);

	bignum_cleanup(b);

berror:
	bignum_cleanup(a);

aerror:
	return 0;
}
