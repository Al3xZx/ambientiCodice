#include <stdio.h>
#include <stdlib.h>
void incrementa(int*, int);
void vectorPrint(int*, int);

void incrementa(int* v, int l){
    int i;
    int* tmp =(int*)malloc(l*sizeof(int));
    printf("indirizzo v= %p\n",v );
    printf("indirizzo tmp= %p\n",tmp );
    for (i = 0; i < l; i++)
        tmp[i]=i+1;
    v=tmp;//tale modifica non ha nessun effetto all'esterno di incrementa
    printf("indirizzo v= %p\n",v );
    printf("indirizzo tmp= %p\n",tmp );
}

void vectorPrint(int* v, int l){
    int i=0;
    printf("[");
    for (i = 0; i < l; i++) {
        if(i != l-1)
            printf(" %d,", *(v+i));
        else
            printf(" %d ]", *(v+i));
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int* v;
    printf("indirizzo v= %p\n\n",v );
    printf("inizia incrementa\n\n");
    incrementa(*v, 5);
    printf("\nfinisce incrementa\n\n");
    printf("indirizzo v= %p\n\n",v );
    //vectorPrint(v, 5);
    return 0;
}
