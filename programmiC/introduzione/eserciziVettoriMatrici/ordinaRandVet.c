#include <stdio.h>
#include <stdlib.h>
/*
2. Scrivere un programma che crei casualmente un array di 13 interi, lo
stampi a video, lo ordini con ordinamento crescente e quindi lo stampi
a video nuovamente.
*/
/*QUESTA SOLUZIONE CON GLI ARREY NON FUNZIONERÀ MAI PERCHÈ LA MEMORIA VERRÀ
SOVRASCRITTA È NECESSARIO L'UTILIZZO DI MALLOC*/
void vectorPrint(int* v, int l);
int* mergeSort(int* v, int l);
int* sort(int* v, int l);
int* merge(int* v1, int l1, int* v2, int l2);
void makeSortVet(int dim);
//sol2
void makeSortVet(int dim){
    int v[dim];
    int i;
    for (i = 0; i < dim; i++) {
        v[i]=rand()%10; //possibile grazie stdlib.h
    }
    int* pv = v;
    vectorPrint(pv, dim);
    pv = mergeSort(pv, dim);
    vectorPrint(pv, dim);
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

int* mergeSort(int* v, int l){
    int* ret = sort(v,l);
    printf("indirizzo ret %p\n", ret);
    vectorPrint(v, l);
    return ret;
}
int* sort(int* v, int l){
    int l1, l2, i;



    if(l==1){
        //ret = v;
        //printf("v singolo = ");
        //vectorPrint(ret, l);
        return v;
    }
    //partiziono
    l1 = l/2;
    l2 = l-l1;
    int v1[l1];
    int v2[l2];
    int* pv1 = v1;
    int* pv2 = v2;
    printf("l1= %d\n", l1);
    printf("l2= %d\n", l2);
    for (i = 0; i < l1; i++) {
        v1[i]=v[i];
        //printf("i= %d\n", i);
    }
    for (i = l1; i < l; i++) {
        v2[i-l1]=v[i];
        //printf("i= %d\n", i);
    }
    printf("v1 = ");
    vectorPrint(v1, l1);
    printf("v2 = ");
    vectorPrint(v2, l2);
    pv1 = sort(pv1, l1);
    pv2 = sort(pv2, l2);
    int* m = merge(pv1, l1, pv2, l2);
    printf("indirizzo m %p\n", m);
    vectorPrint(m, l1+l2);
    return m;
}
int chiamateMerge=0;
int* merge(int* v1, int l1, int* v2, int l2){
    int i,j,k;
    i=j=k=0;
    int ret[l1+l2];
    int* pret = ret;
    while(i<l1 && j<l2){
        if(*(v1+i) <= *(v2+j)){
            ret[k]=*(v1+i);
            k++;i++;
        }else{
            ret[k]=*(v2+j);
            k++;j++;
        }
    }
    while(i<l1){
        ret[k]=*(v1+i);
        k++;i++;
    }
    while(j<l2){
        ret[k]=*(v2+j);
        k++;j++;
    }
    //printf("%d mergeRet = ", ++chiamateMerge);
    //vectorPrint(pret, l1+l2);
    //printf("indirizzo pret %p\n", pret);
    return pret;
    //return ret;non è possibile restituire ret perchè è una costante
}
int main(int argc, char const *argv[]) {
    makeSortVet(13);
    return 0;
}
