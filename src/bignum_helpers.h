#include "../include/bignum.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool is_digit(char c);

bool is_valid_char(char c);

bool has_floating_point(const bignum_t* num);

unsigned int get_true_length(const bignum_t* num);

unsigned short get_digit_at(const bignum_t* num, int power);

int get_minimal_power(const bignum_t* num);
