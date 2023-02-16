#include <shanks.h>

void __shanks__init__(int p, int a, int vars[5]){
    int n=1;
    int k=0, s= p-1;
    int r, b;
    
// Déterminer n
    while(n++ < p-1){
        if( jacobi(n, p) == -1 ) break;
    }

// Déterminer k et s tq p - 1 = 2^k * s
    while( s!= 0 && !(s&1) ){
        k++;
        s= s>>1;
    }

// Déterminer r et b
    r= mod_expo(a, (s+1)>>1, p);
    b= mod_expo(n, s, p);

    vars[0]= n, vars[1]= k, vars[2]= s;
    vars[3]= r, vars[4]= b;
}


// Fonction Shanks-Tonelli principale
int shanks(int a, int p){
    int n, k, s;
    int r, b;
    int vars[5];

    __shanks__init__(p, a, vars);

    // p-1= r*2^s
    // b= n^s
    // r= a^( (s+1)/2 )

    n= vars[0], k= vars[1], s= vars[2];
    r= vars[3], b= vars[4];

// Calcul de l = (r^2 * a^(-1)) mod p
    int l= (mod_expo(r, 2, p) * mod_inv(a, p) ) % p;


    if( DEBUG_ON ) printf("%d= 2^k * s = 2^%d * %d\nn= %d\n", p-1, k, s, n);
    if( DEBUG_ON ) printf("r= %d\nb= %d\n", r, b);
    if( DEBUG_ON ) printf("l= (r^2) * (a^(-1)) = %d\n\n", l);

    int j_, j;
    int b_, res;

// Première étape faite hors boucle
// j_ stocke le bit de l'étape précédente

    if( k == 1 ) res= 1;//l;
    else res= mod_expo(l, (1<<(k-2)), p);
    // printf("cc\n");

    j_= (res == 1 ? 0 : 1);
    j= j_;

    b_= (j_ ? b : 1);



    if( DEBUG_ON )  printf("Etape %d\n", 0);
    if( DEBUG_ON )  printf("b_ = %d\n", b_);
    if( DEBUG_ON )  printf("j_%d= %d\n\n", 0, j_);

    for(int i=1; i< k-1; i++){

    // Pour toute étape i

    //  Calculer b_i= ( b^(j0+2j1+...)^(k-2-i) )^2 mod p
    //              = ( b_(i-1) * b^(2^(i-1)) )^2 mod p si j_(i-1) == 1
    //              = ( b_(i-1) )^2 mod p sinon
        b_= b_ * (j_ ? ( mod_expo(b, (1 <<(i-1)), p ) ) : 1);
        b_= mod_expo(b_, 2, p);

    //  Calculer res= (b_ * l) mod p
        res= ( ( b_ * l ) % p );
        res= mod_expo(res, (1<< (k-2-i)), p);

    // j_ devient le bit de l'étape i;
    // Ajout du bit trouvé dans le resultat à la (i+1)-eme place
        j_= (res == 1 ? 0 : 1);
        j|= j_<<i;

        if( DEBUG_ON )  printf("Etape %d\n", i);
        if( DEBUG_ON )  printf("b_ = %d\n", b_);
        if( DEBUG_ON )  printf("res= %d mod p\n", res);
        if( DEBUG_ON )  printf("j_%d= %d\n\n", i, j_);
    }

    return (mod_expo(b, j, p) *  r) % p;
}