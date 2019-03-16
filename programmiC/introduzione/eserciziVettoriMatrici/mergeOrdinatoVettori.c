#include <stdio.h>
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
    return pret;
    //return ret;non è possibile restituire ret perchè è una costante
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
    int vett1[10] = {2, 5 ,9, 14, 15, 20, 25, 27, 30, 32};
    vectorPrint(vett1, 10);
    int vett2[10] = {3, 5, 10, 11, 12, 22, 23, 24, 26, 27};
    vectorPrint(vett2, 10);
    int* sol=merge(vett1, 10, vett2, 10);
    vectorPrint(sol, 20);
    return 0;
}
