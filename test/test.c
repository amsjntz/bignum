#include "../include/bignum.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
	bignum_t* a = bignum_create_from_string("-010");
	bignum_t* b = bignum_create_from_double(-0.00011);

	if (a == NULL) {
		printf("a is not a number\n");
		return -1;
	} else {
		char* astr = bignum_to_string(a);
		printf("a = %s\n", astr);
		free(astr);
		bignum_cleanup(a);
	}

	if (b == NULL) {
		printf("b is not a number\n");
		return -1;
	} else {
		char* bstr = bignum_to_string(b);
		printf("b = %s\n", bstr);
		free(bstr);
		bignum_cleanup(b);
	}

	return 0;
}
