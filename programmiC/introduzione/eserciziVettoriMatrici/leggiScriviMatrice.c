#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere un programma che legga una matrice da tastiera, la stampa a
video e libera la memoria*/
void matrixPrint(int**, int, int);
void vectorPrint(int*, int);
int main(int argc, char const *argv[]) {
    int righe, colonne, i, j, k;
    printf("specificare il numero di righe della matrice >> ");
    scanf("%d",&righe);
    printf("\nspecificare il numero di colonne della matrice >> ");
    scanf("%d",&colonne);
    printf("righe = %d, colonne = %d\n", righe, colonne);

    int** mat = (int**) malloc(righe*sizeof(int*));
    if(mat==NULL){
        printf("memoria insufficiente!!/n");
        return 1;
    }
    for (i = 0; i < righe; i++) {
        mat[i]=(int*)malloc(colonne*sizeof(int));
        if(mat[i]==NULL){
            printf("memoria insufficiente!!/n");
            printf("libero la memoria...\n");
            for(k = 0; k<i;k++)
                free(mat[k]);
            free(mat);
            return 1;
        }
        for(j=0;j<colonne;j++){
            printf("inserire l'elemento mat[%d][%d]>> ",i,j );
            scanf("%d",&mat[i][j] );
        }
    }
    matrixPrint(mat,righe,colonne);
    printf("libero la memoria...\n");
    for (i = 0; i < righe; i++)
        free(mat[i]);
    free(mat);

    return 0;
}
void matrixPrint(int** mat, int r, int c){
    int i;
    for (i = 0; i < r; i++){
        vectorPrint(mat[i],c);
    }
    printf("\n");
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
