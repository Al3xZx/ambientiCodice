#include <stdio.h>
#include <stdlib.h>
/*
2. Scrivere un programma che crei casualmente un array di 13 interi, lo
stampi a video, lo ordini con ordinamento crescente e quindi lo stampi
a video nuovamente
*/
void vectorPrint(int* v, int l);
int* mergeSort(int* v, int l);
int* sort(int* v, int l);
int* merge(int* v1, int l1, int* v2, int l2);
void makeSortVet(int dim);
/*sol2*/
void makeSortVet(int dim){
    int* v = (int*) malloc(dim*sizeof(int));
    if(v==NULL){
        printf("memoria insufficiente!!\n");
        return;
    }
    int i;
    for (i = 0; i < dim; i++) {
        v[i]=rand()%100; /*possibile grazie stdlib.h*/
    }
    vectorPrint(v, dim);
    v = mergeSort(v, dim);
    if(v==NULL){
        printf("memoria insufficiente!!\n");
        return;
    }
    vectorPrint(v, dim);
    free(v);
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
    return sort(v,l);
}
int* sort(int* v, int l){
    int l1, l2, i;
    int* v1;
    int* v2;
    int* m;
    if(l==1){
        return v;
    }
    l1 = l/2;
    l2 = l-l1;
    /*partiziono*/
    v1=(int*) malloc(l1*sizeof(int));
    if(v1==NULL){
        printf("memoria insufficiente!!\n");
        return NULL;
    }
    v2=(int*) malloc(l2*sizeof(int));
    if(v2==NULL){
        printf("memoria insufficiente!!\n");
        free(v1);
        return NULL;
    }
    for (i = 0; i < l1; i++) {
        v1[i]=v[i];
    }
    for (i = l1; i < l; i++) {
        v2[i-l1]=v[i];
    }
    v1 = sort(v1, l1);
    v2 = sort(v2, l2);
    m = merge(v1, l1, v2, l2);
    free(v1);free(v2);
    return m;
}

int* merge(int* v1, int l1, int* v2, int l2){
    int i,j,k;
    int* ret;
    i=j=k=0;
    ret = (int*) malloc((l1+l2)*sizeof(int));
    if(ret==NULL){
        printf("memoria insufficiente!!\n");
        free(v1);free(v2);
        return NULL;
    }
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
    return ret;
}
int main(int argc, char const *argv[]) {
    makeSortVet(10);
    return 0;
}
