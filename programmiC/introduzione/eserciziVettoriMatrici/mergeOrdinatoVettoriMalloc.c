#include <stdio.h>
#include <stdlib.h>
/*Si sviluppi un programma in linguaggio C che riceva in ingresso due vettori di
interi, ciascuno di 10 elementi. Supponendo che i due vettori siano inseriti già
ordinati in modo crescente, il programma deve creare e stampare un terzo vettore
che rappresenti la “fusione” dei due vettori acquisiti, ovvero che contenga tutti i 20
elementi ordinati tra loro in modo crescente.
Ad esempio, se il primo vettore contiene gli elementi
2 5 9 14 15 20 25 27 30 32
e il secondo vettore contiene gli elementi
3 5 10 11 12 22 23 24 26 27
Il programma crea e stampa un vettore contenente i seguenti elementi:
2 3 5 5 9 10 11 12 14 15 20 22 23 24 25 26 27 27 30 32*/
#define N 10
void stampa(int*, int);
void merge(int*, int*, int*);void leggi(int*, int);
int* newArray(int);
int main(int argc, char const *argv[]) {
    int* v1=newArray(N);
    int* v2=newArray(N);
    int* v3=newArray(2*N);
    //v1=(int*)malloc(N*sizeof(int));
    if (v1==NULL) {
        printf("%s\n","memoria non disponibile");
        return 1;
    }
    //v2=(int*)malloc(N*sizeof(int));
    if (v2==NULL) {
        printf("%s\n","memoria non disponibile");
        free(v1);
        return 1;
    }
    //v3=(int*)malloc(2*N*sizeof(int));
    if (v3==NULL) {
        printf("%s\n","memoria non disponibile");
        free(v1);free(v2);
        return 1;
    }
    leggi(v1,N);leggi(v2,N);
    merge(v1,v2,v3);
    stampa(v1,N);stampa(v2,N);stampa(v3,2*N);
    free(v1);free(v2);free(v3);
    return 0;
}//main

int* newArray(int n){
    int* ret;
    ret=(int*)malloc(n*sizeof(int));
    return ret;
}//newArray
void stampa(int* v, int n){
    int i;
    printf("[ ");
    for(i=0;i<n;i++){
        if(i<n-1)
            printf("%d, ", v[i]);
        else
            printf("%d ]\n", v[i]);
    }
}//stampa
void leggi(int* v, int n){
    int i;
    for(i=0;i<n;i++){
        printf("inserire l'lemento %d >> ",i);
        scanf("%d",&v[i]);
    }
}//leggi
void merge(int* v1, int* v2, int* v3){
    int i,j,k,n;
    i=0;j=0;k=0;
    n=2*N;
    while(k<n){
        if(v1[i]<v2[j]){
            v3[k]=v1[i];
            i++;k++;
        }else{
            v3[k]=v2[j];
            j++;k++;
        }
    }
}//merge
