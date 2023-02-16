#include <primality.h>


// long pow(long a, long n) {
//    long result = 1;
//    while (n > 0) {
//       if (n & 1) result *= a;
//       n >>= 1;
//       a *= a;
//    }

//    return result;
//  }
// long modpow(long a, long n, long m) {
//    long result = 1;
//    while (n > 0) {
//       if (n & 1) result = (result * a) % m;
//       n >>= 1;
//       a = (a * a) % m;
//    }

//    return result;
//  }
// long legendre(long a, long p){
//     long tmp;

//     // cas p= 0, 1, 2

//     switch(p){
//         case 0: return 0;
//         case 1: return 1;
//         case 2: tmp= p%8;
//             return (tmp == 1 || tmp == 7 ? 1 : -1);
//     }

//     //Sinon
//     tmp= modpow(a, (p-1) / 2, p);
//     return tmp == p - 1 ? -1 : tmp;
// }

// long jacobi(long b, long n){
//     int p_i= 0, a_i= 0;
//     int res= 1;

//     for(p_i=3; n > 2; p_i++){
//         a_i= 0;
//         while(n % p_i == 0){    // Tant que n= kp
//             n/= p_i; 
//             a_i++;
//         }
//         if(a_i != 0)
//             res*= pow(legendre(b, p_i), a_i);
//     }
//     return res;
// }

int factor_two(long n, long *s, long *d){
    if( n % 2 != 0 )    return 1;   // n doit ête pair

    for( *s= 0, *d= 0; n != 0 && !(n & 1); n= n>>1, (*s)++);
    *d= n;
    return 0;
}

bool temoin_miller_rabin(long n, long a){
    long n_1= n - 1;
    long s, d;

    if( factor_two(n_1, &s, &d) ){          // n_1= 2^s * d
        printf("Erreur Miller-Rabin");
        return true;
    }

    long x= mod_expo(a, d, n);
    if( x == 1 || x == n_1 )    return false;
    
    for(; s > 0; s--){

        x= mod_expo(x, 2, n);
        if( x == n_1 )    return false;

    }
    return true;
}



bool primality_fermat(long n){
    long a= ( rand() % (n - 1) ) + 1;
    if(mod_expo(a , n-1, n) == 1)
        return true;
    return false;
}

bool primality_solovay_strassen(long n, int k){

    for(; k > 0; k--){
        long a= (rand() % (n - 2) ) + 2;
        int jac= jacobi(a, n);
        jac= jac >= 0 ? jac : jac+n;

        // printf("Jac(%ld,%ld)= %d\n", a, n, jac);
        if( jac == 0 || jac != mod_expo(a, (n - 1) / 2, n))
            return false;
    }

    return true;
}

bool primality_miller_rabin(long n, int k){
    long n_1= n - 1;

    for(; k > 0; k--){
        long a= (rand() % (n_1 - 2) ) + 2;
        if( temoin_miller_rabin(n, a) )
            return false;
    }

    return true;
}
