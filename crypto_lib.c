#include "headers/karatsuba.h"
#include "headers/shanks.h"
#include "headers/primality.h"
#include "headers/pollard.h"

// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

void process_karatsuba(){
    int n, m;
    printf("Let's calculate of n * m\n");
    
    printf("Choose n : "); scanf("%d", &n);
    printf("Choose m : "); scanf("%d", &m);
    printf("\n");

    if(DEBUG_ON) printf("n= %d ; m= %d\n\n", n, m);

    int res= karatsuba(n, m);
    
    printf("n * m = %d * %d = %d\n", n, m, res);
}

void process_shanks(){
    int a, p;

    printf("Let's calculate x where a = x^2 mod p : \n");
    
    printf("Choose a : "); scanf("%d", &a);
    printf("Choose p : "); scanf("%d", &p);
    printf("\n");

    if(DEBUG_ON) printf("a= %d ; p= %d\n", a, p);

    int x= shanks(a, p);

    printf("Square root of %d mod p = %d\n", a, x);
}

void process_primality(){
    long N;
    printf("Primality test of n\n");
    printf("Choose n : "); scanf("%ld", &N);
    printf("\n");

    if(N >= MAX_LONG_SIZE) return;
    if( N  < 0 ){ printf("n must be greater or equal to 0\n"); return; }
    if( N <= 1 ){ printf("1 is not prime\n"); return; }
    if( N <= 2 ){ printf("%ld is prime\n", N); return; }
    if( !(N&1) ){ printf("N is not prime\n"); return; }

    printf("Primality test of Fermat : %d\n",  primality_fermat(N));
    printf("Primality test of Solovay-Strassen : %d\n",  primality_solovay_strassen(N, SS_TEST_ROUND));
    printf("Primality test of Miller-Rabin : %d\n",  primality_miller_rabin(N, SS_TEST_ROUND) );
}

void process_factor(){
    // n1= 52590354472497239257283147;
    // n2= 52590354464570687296135717939981;

    // mpz_t P, A;

    // mpz_init_set_ui(P, 10);
    // mpz_init_set_ui(A, 10);
    // int n= 2041;
    // mpz_init_set_ui(N, 2041);

    char N_str[50];
    mpz_t N, p, q;
    mpz_init(p);
    mpz_init(q);

    printf("Let's factorize N\n");
    printf("Choose N : ");
    printf("\n");

    if( !scanf(" %49[0-9 ]", N_str) )
        return;

    mpz_init_set_str(N, N_str, 10);

    if( mpz_probab_prime_p(N, 24) ){
        gmp_printf("%Zd is prime.\n", N);
        return;
    }

    facto_pollard(p, N);
    mpz_cdiv_q(q, N, p);

    gmp_printf("Factorization of Rho-Pollard on %Zd = p * q with\n", N);
    gmp_printf("p: %Zd\n", p);
    gmp_printf("q: %Zd\n", q);

}

int main(int argc, char** argv){
    srand( time( NULL ) );
    
    int c;
    printf("Welcome on my super cryptographic lib !\n");
    
    while(1){
        printf("\n************ Choose a tool **************\n");
        printf("*\t\t\t\t\t*\n");
        printf("* 1 - Multiplication Karatsuba \t\t*\n");
        printf("* 2 - Root Shanks-Tonelli    \t\t*\n");
        printf("* 3 - Primality Test        \t\t*\n");
        printf("* 4 - Factorization Rho-Pollard\t\t*\n");
        printf("* 0 - Exit \t\t\t\t*\n");
        printf("*\t\t\t\t\t*\n");
        printf("*****************************************\n");

        printf("Your choice : "); scanf("%d", &c);
        fflush(stdin);

        printf("\n");

        switch(c){
            case 1: process_karatsuba(); break;
            case 2: process_shanks(); break;
            case 3: process_primality(); break;
            case 4: process_factor(); break;
            case 0:default: printf("Au revoir !\n"); return 0;

        }

        printf("\n*****************************************\n");
        printf("*\t\t\t\t\t*\n");
        printf("*\tPress [ENTER] to Continue\t*\n"); 
        printf("*\t\t\t\t\t*\n");
        printf("*****************************************\n");

        while(getchar()!='\n'); // option TWO to clean stdin
        // fflush(stdin);
        getchar(); // wait for ENTER

    }
    
}