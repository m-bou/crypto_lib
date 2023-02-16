#ifndef PRIMALITY_H
#define PRIMALITY_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <utils.h>

bool    primality_fermat(long);
bool    primality_solovay_strassen(long, int);
bool    primality_miller_rabin(long, int);

#endif
