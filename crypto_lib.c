#include "headers/karatsuba.h"
#include "headers/shanks.h"
#include "headers/primality.h"

// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

void process_karatsuba(){
    int n, m;
    printf("Calcul de n*m : ");
    
    printf("Choisir n : "); scanf("%d", &n);
    printf("Choisir m : "); scanf("%d", &m);

    if(DEBUG_ON) printf("n= %d ; m= %d\n\n", n, m);

    int res= karatsuba(n, m);
    
    printf("n * m = %d * %d = %d\n", n, m, res);
}

void process_shanks(){
    int a, p;

    printf("Calcul de sqrt(a) mod p : \n");
    
    printf("Choisir a : "); scanf("%d", &a);
    printf("Choisir p : "); scanf("%d", &p);

    if(DEBUG_ON) printf("a= %d ; p= %d\n", a, p);

    int x= shanks(a, p);

    printf("Racine carrée de %d mod p = %d\n", a, x);
}

void process_primality(){
    long N;
    printf("Test primalité de n\n");
    printf("Choisir n : "); scanf("%ld", &N);

    if( N <= 2 || N >= MAX_LONG_SIZE)
        return;

    if( !(N&1) ){
        printf("Entier pair != 2 donc non premier\n\n");
        return;
    }

    srand( time( NULL ) );
    printf("Test de primalité de Fermat : %d\n",  primality_fermat(N));
    printf("Test de primalité de Solovay-Strassen : %d\n",  primality_solovay_strassen(N, SS_TEST_ROUND));
    printf("Test de primalité de Miller-Rabin : %d\n",  primality_miller_rabin(N, SS_TEST_ROUND) );
}

// void process_factor(int argc, char** argv){
//     mpz_t N, p, q;
//     mpz_init(p);
//     mpz_init(q);

//     // n1= 52590354472497239257283147;
//     // n2= 52590354464570687296135717939981;

//     // mpz_t P, A;

//     // mpz_init_set_ui(P, 10);
//     // mpz_init_set_ui(A, 10);
//     // int n= 2041;
//     // mpz_init_set_ui(N, 2041);

//     if(argc == 2)   mpz_init_set_str(N, argv[1], 10);
//     else{
//         printf("usage : pollard_facto N\n");
//         return 1;
//     }

//     if( mpz_probab_prime_p(N, 24) ){
//         gmp_printf("%Zd est premier.\n", N);
//         return;
//     }

//     facto_pollard(p, N);
//     mpz_cdiv_q(q, N, p);

//     gmp_printf("Rho de pollard sur %Zd\n", N);
//     gmp_printf("p: %Zd\n", p);
//     gmp_printf("q: %Zd\n", q);

//     return 0;
// }

int main(int argc, char** argv){
    int c;
    printf("Bienvenue dans ma super bibliothèque cryptographique !\n");
    
    while(1){
        printf("\n*********** Choissir un outil ***********\n\n");
        printf("* 0 - Exit \t\t\t\t*\n");
        printf("* 1 - Multiplication karatsuba \t\t*\n");
        printf("* 2 - Racine Shanks-Tonelli    \t\t*\n");
        printf("* 3 - Test de Primalité        \t\t*\n");
        printf("\t\t\t\t\t*\n");
        printf("*****************************************\n");

        printf("Votre choix : "); scanf("%d", &c);
        printf("\n");

        switch(c){
            case 1: process_karatsuba(); break;
            case 2: process_shanks(); break;
            case 3: process_primality(); break;
            case 0:default: printf("Au revoir !\n"); return 0;

        }
    }
    
}