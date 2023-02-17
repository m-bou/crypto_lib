#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gmp.h>

#include <pollard.h>

/*
*   Définition de f, la fonction de pas aléatoire
*/

void facto_f(mpz_t x_i){
    mpz_pow_ui(x_i, x_i, 2);
    mpz_add_ui(x_i, x_i, 1);
}

long int facto_log(long int n){
    int h=0;
    while( (n>>= 1) ) h++;
    return h;
}


void facto_pollard(mpz_t p, mpz_t N){
    mpz_t x_i, x_j, tmp;

    mpz_init(tmp);
    mpz_init_set_ui(x_j, 1);
    mpz_init_set_ui(x_i, 2);

    long int h=0; //, j=0;
    long int i= 1;
    long int max_i= (1<<(h+1));
    
    while(true){

        // printf("h= %d, j= %d, i= %d, max_i= %d\n", h, j, i, max_i);
        // gmp_printf("i,j= %d,%d : x_i= %Zd\n\n", i, j, x_i);
        mpz_sub(tmp, x_i, x_j);     // tmp = x_i - x_j
        mpz_gcd(p, tmp, N);
        
        // printf("gcd = %d\n", mpz_cmp_ui(p, 1));
        if( mpz_cmp(p, N) && mpz_cmp_ui(p, 1) )
            return;

        if( i >= max_i){
            h= facto_log(i);
            // j= (1<<h) - 1;
            max_i= (1<<(h+1));

            mpz_set(x_j, x_i);
            mpz_mod(x_j, x_j, N);

            // printf("*** x_j updated !\n");
            // gmp_printf("x_j= %Zd\n\n", x_j);

        }

        facto_f(x_i);
        mpz_mod(x_i, x_i, N);

        i++;

    }
    // printf("%d\n", facto_log(2));
}