#include <utils.h>

int euclide_etendu(int a, int b, int uv[2]){
    if(!b){
        uv[0]= 1;
        uv[1]= 0;
        
        return a;
    }
    
    int d= euclide_etendu(b, a % b, uv);
    int u= uv[0], v= uv[1];
    unsigned int l= a / b;

    uv[0]= v;
    uv[1]= u - l*v;
 
    return d;
}

int mod_inv(int a, int p){
    int uv[2];

    euclide_etendu(a, p, uv);       // a*uv[0] + p*uv[1] == d; ==> a*uv[0] = d mod p
    
    int a_1= (uv[0] + p ) % p;

    if(DEBUG_ON) printf("CALCUL mod_inv : a^(-1) * a = %d * %d == %d mod %d\n", a_1, a, (a*a_1) % p, p);

    return a_1;
}

long mod_expo(long b, long e, long n){
    long res= 1;
    long _b= b;
    long _e= e;
    
    while(e){
        if( e&1 ) res= (res * b) % n;
        e >>= 1;
        b= (b*b) %n;
    }

    if(DEBUG_ON) printf("CALCUL mod_expo : b^e mod n = %ld ^ %ld mod %ld == %ld mod %ld\n", _b, _e, n, res, n);


    return res;
}

int jacobi(int a, int n){
    int s=1;
    a= (a % n);

    if( !a )            return 0;
    if( a && n == 2)    return 1;

// Si a pair
    while( !(a&1) && a != 2 ){
        s*= jacobi(2, n);
        a>>= 1;
    }


// Si n pair
    while( !(n&1) && n != 2 ){
        s*= jacobi(a, 2);
        n>>= 1;
    }

// Si cas de base lorsque n et m impair

    int k1= (n % 4);
    if( a == -1 && ( k1 == 1) )    return 1;
    if( a == -1 && ( k1 == 3) )    return -1;

    int k2= (n % 8);
    if( a ==  2 && ( k2 == 1 || k2 == 7) )  return 1;
    if( a ==  2 && ( k2 == 3 || k2 == 5) )  return -1;

    
    return s*( (a % 4 == 3) && (n % 4 == 3) ? (-1)*jacobi(n, a) : jacobi(n, a) );
}
