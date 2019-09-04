/*Esercizio 1 (Programmazione in C, 8 punti)
Scrivere un programma in C per la gestione di matrici di interi, che contenga i seguenti metodi:
-Una funzione create, che riceve due interi (dimensione di righe e colonne),
 crea una matrice delle dimensioni indicate, e restituisce il suo puntatore.
-Un metodo read per la lettura di una matrice da tastiera.
-Un metodo print per la stampa della matrice su output.
-Un metodo restituisci_max_min_vett che restituisce (in maniera opportuna usando i puntatori)
 il massimo della matrice, il minimo della sua diagonale e un vettore V costruito come indicato di seguito.
 Il vettore V è formato da tutti gli elementi della matrice che si trovino nelle righe dispari
 e che siano maggiori di 2 volte il minimo della diagonale della matrice.
-Il metodo main che dichiara e alloca la matrice e invoca opportunamente i metodi precedenti.*/

#include <stdio.h>
#include <stdlib.h>

int** create(int r, int c){
    int i,k;
    int** ret;
    ret = (int**) malloc(r*sizeof(int*));
    if (ret==NULL) {
        printf("ERRORE memoria non disponibile\n");
        exit(-1);
    }
    for (i = 0; i < r; i++) {
        ret[i] = (int*) malloc(c*sizeof(int));
        if (ret[i]==NULL) {
            printf("ERRORE memoria non disponibile\n");
            for (k = 0; k < i; k++) {
                free(ret[k]);
            }
            free(ret);
            exit(-1);
        }
    }
    return ret;
}

void read(int** mat,int r, int c) {
    int i,j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("inserire elemento %d %d > ", i, j);
            scanf("%d",&mat[i][j]);
        }
    }
}
void print(int** mat,int r, int c) {
    int i,j;
    for (i = 0; i < r; i++) {
        printf("[ ");
        for (j = 0; j < c-1; j++) {
            printf("%d, ", mat[i][j]);
        }
        printf("%d ]\n",mat[i][c-1]);
    }
}

int* restituisci_max_min_vett(int** mat,int r, int c, int* max, int* min, int* dimVet) {
    int i,j;
    int* vet;
    *max=mat[0][0];
    *min=mat[0][0];
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (*max < mat[i][j])
                *max = mat[i][j];
            if(i == j && *min > mat[i][j])
                *min = mat[i][j];
        }
    }
    vet=NULL;
    *dimVet=0;
    for (i = 1; i < r; i+=2)
        for (j = 0; j < c; j++) {
            if (mat[i][j] > (min[0])*2) {
                if(*dimVet==0){
                    vet=(int*)malloc(sizeof(int));
                    if(vet==NULL){
                        printf("ERRORE memoria non disponibile\n");
                        exit(-1);
                    }
                }else{
                    vet=(int*)realloc(vet,(dimVet[0]+1)*sizeof(int));
                    if(vet==NULL){
                        printf("ERRORE memoria non disponibile impossibile reallocare\n");
                        exit(-1);
                    }
                }
                vet[dimVet[0]]=mat[i][j];
                printf("aggiungo %d in posizione %d\n", mat[i][j],*dimVet);
                *dimVet+=1;
            }
        }
        return vet;
}

int main(int argc, char const *argv[]) {
    int r,c,min,max,dimVet,i,k;
    int** m;
    int* v;
    r=4;c=4;
    m=create(r,c);
    read(m,r,c);
    printf("la matrice è:\n");
    print(m,r,c);
    v = restituisci_max_min_vett(m, r, c, &max, &min, &dimVet);
    printf("il massimo della matrice è %d il minimo della diagonale è %d\n",max,min);
    printf("il vettore è:\n");
    printf("[ ");
    for (i = 0; i < dimVet; i++)
        printf("%d ", v[i]);
    printf("]\n");

    printf("libero spazio...\n");
    for (k = 0; k < r; k++) {
        free(m[k]);
    }
    free(m);
    free(v);
    return 0;
}
