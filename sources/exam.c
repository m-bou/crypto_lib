#include <exam.h>
#include <math.h>

// int exam_factor(long n){
//     int k= 0;
//     n--;

//     while( ( (n&1) == 0) ){
//         n>>= 1;
//         k++;
//     }

//     if(n == 1)
//         return k;
//     return -1;
// }

int s(int i){
    if( i == 0 ) return 4;
    return pow(s(--i),2) - 2;
}

void exam(){
    long M, k;
    printf("Choose k : "); scanf("%ld", &k);
    M= pow(2, k) - 1;

    if( M == 0 || M == 1){ printf("Not prime\n"); return; }
    if( M == 2){ printf("Prime\n"); return; }

    int is_prime = ( (s(k-2) % M) == 0 );

    printf(" Is prime : %d\n", is_prime);
}
