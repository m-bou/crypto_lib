#ifndef UTILS_H
#define UTILS_H

#define DEBUG_ON 0
#define MASK(n) ( (1 << (n)) - 1 )

#define SS_TEST_ROUND 20
#define MR_TEST_ROUND 20

// #define MAX_LONG_SIZE 50000
#define MAX_LONG_SIZE (1<<30)

#include <stdio.h>
#include <stdlib.h>

int euclide_etendu(int, int, int[2]);
int mod_inv(int, int);

// Exponentiation modulaire
long mod_expo(long, long, long);
int jacobi(int, int);

#endif