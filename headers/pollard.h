#ifndef FACTO_H
#define FACTO_H

#include <stdbool.h>
#include <gmp.h>

// #define SS_TEST_ROUND 20
// #define MR_TEST_ROUND 20


void facto_f(mpz_t);
int facto_log(int);
void facto_pollard(mpz_t, mpz_t);
// void crible()
#endif