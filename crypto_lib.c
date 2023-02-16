#include "headers/karatsuba.h"

void process_karatsuba(int argc, char** argv){
    int n, m;
    
    if( argc != 3 ){
        printf("\nERROR usage : ./main n m \n\n");
        return 1;
    }

    sscanf (argv[1],"%d",&n);
    sscanf (argv[2],"%d",&m);

    if(DEBUG_ON) printf("n= %d ; m= %d\n\n", n, m);

    int res= karatsuba(n, m);
    
    printf("n * m = %d * %d = %d\n", n, m, res);
    return 0;
}

int main(int argc, char** argv){
    int c;
    printf("Bienvenue dans ma super bibliothèque cryptographique !!\n");
    
    while(true){
        printf("Choississez un outil :\n");
        printf("*** 1 - Karatsuba n * m \n");
        printf("*** 0 - Exit \n");
        scanf("%d", &c);

        switch(c){
            case 0: printf("Au revoir !"); return 0;
            case
        }
    }
    
}