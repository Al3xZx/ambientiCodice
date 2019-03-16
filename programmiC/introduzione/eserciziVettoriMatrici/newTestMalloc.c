#include <stdio.h>
#include <stdlib.h>
int* incrementa(int*, int);
void vectorPrint(int*, int);

int* incrementa(int* v, int l){
    int i;
    int* tmp =(int*)malloc(l*sizeof(int));
    printf("indirizzo v= %p\n",v );
    printf("indirizzo tmp= %p\n",tmp );
    for (i = 0; i < l; i++)
        tmp[i]=i+1;
    return tmp;
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
    v = incrementa(v, 5);
    printf("\nfinisce incrementa\n\n");
    printf("indirizzo v= %p\n\n",v );
    vectorPrint(v, 5);
    return 0;
}
