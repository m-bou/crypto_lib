
#include <karatsuba.h>

int get_k(int n, int m){
    int k=0;
    n= (n< 0 ? -n : n);
    m= (m< 0 ? -m : m);
    
    while(n || m)
        n= n>>1, m= m>>1, k++;

    return (k == 0 ? 0 : k);
}

/*
    Génère la paire d'argument (a,b) tq m= a*2^(k/2) + b
    Stocke la paire (a,b) dans le tableau elt tq elt[0]= a et elt[1]= b;
*/

int __karatsuba__generate__params(int m, int elt[2], int k_){
    int alpha, beta;

    beta= MASK(k_) & m;
    alpha= m >> k_;

    elt[0]= alpha;
    elt[1]= beta;

    return 0;
}

int __karatsuba(int n, int m, int k){
    if( n == 0 || m == 0 ) return 0;
    if(n < m) return __karatsuba(m, n, k);

    int is_neg= 0;

    if( n < 0 ) n= -n, is_neg++; 
    if( m < 0 ) m= -m, is_neg++;
    if( m == 1 ) return is_neg&1 ? -n : n;
    

    int elt_n[2];
    int elt_m[2];

    int _k=  ((k+1)>>1); // <===> round( k/2 )
    k= (_k << 1 ); // k= k*2


    __karatsuba__generate__params(n, elt_n, _k);
    __karatsuba__generate__params(m, elt_m, _k);


    int a= elt_n[0], b= elt_n[1];
    int c= elt_m[0], d= elt_m[1];

    int m1= __karatsuba(a, c, _k);
    int m2= __karatsuba(b, d, _k);
    int m3= __karatsuba((a - b), (c - d), _k);


    int res= (m1 << k) + ( ( m1 + m2 - m3 ) << _k ) + m2;
    
    //Gérer les problèmes de signe
    res= (is_neg&1 ? -res : res);

    int res_expected= (is_neg ? -n*m : n*m);

    if(DEBUG_ON){
        printf("k= %d; k/2= %d;\n", k, _k);
        printf("m1= %d; m2= %d; m3= %d\n\n", m1, m2, m3);
        printf("n: a= %d; b= %d\n", elt_n[0], elt_n[1]);
        // printf("===> n = %d = a * 2^(k/2) + b = %d\n\n", n, ( elt_n[0] << _k ) + elt_n[1] );
        printf("m: c= %d; d= %d\n", elt_m[0], elt_m[1]);
        // printf("===> m = %d = c * 2^(k/2) + d = %d\n\n", m, ( elt_m[0] << _k ) + elt_m[1] );

        printf("RES : %d == %d ? %s\n\n\n", res_expected, res, res == res_expected ? "OUI" : "NON");
    }

    return res;
}


int karatsuba(int n, int m){
    int k= get_k(n, m);
    return __karatsuba(n, m, k);
}