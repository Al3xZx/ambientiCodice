#include <stdio.h>
#include <stdlib.h>
/*Scrivere un programma per la gestione di matrici di double, che
contenga i seguenti metodi:
Una funzione create, che riceve due interi (dimensione di righe e
colonne), crea una matrice delle dimensioni indicate, e restituisce
il suo puntatore.
Un metodo erase, che azzera tutti gli elementi della matrice.
Un metodo read per la lettura di una matrice da tastiera.
Un metodo print per la stampa della matrice su output.
Un metodo mult che effettui il prodotto di due matrici, restituendo
il puntatore alla matrice risultante.*/
double** create(int, int);
void erase(double**, int, int);
void read(double**, int, int);
void print(double**, int, int);
double** mult(double**, int, int, double**, int, int);

double** create(int r, int c){
    int i,k;
    double** ret = (double**)malloc(r*sizeof(double*));
    if(ret == NULL){
        printf("memoria insufficiente!!\n");
        return NULL;
    }
    for(i=0;i<r;i++){
        ret[i]=(double*)malloc(c*sizeof(double));
        if(ret[i]==NULL){
            printf("memoria insufficiente!!\n");
            for(k=0;k<i;k++)
                free(ret[k]);
            free(ret);
            return NULL;
        }
    }
    return ret;
}

void erase(double** m, int r, int c){
    int i,j;
    if(m==NULL){
        printf("matrice non disponibile\n");
        return;
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            m[i][j]=0;
}

void read(double** m, int r, int c){
    int i,j;
    if(m==NULL){
        printf("matrice non disponibile\n");
        return;
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++){
            printf("inserire l'elemento [%d, %d] >> ",i,j);
            scanf("%lf",&m[i][j]);
        }
        /*printf("\n");*/
}

void print(double** m, int r, int c){
    int i,j;
    if(m==NULL){
        printf("matrice non disponibile\n");
        return;
    }
    for (i = 0; i < r; i++){
        printf("| ");
        for (j = 0; j < c; j++){
            if(j!=c-1)
                printf("%3.2lf, ",m[i][j]);
            else
                printf("%3.2lf |",m[i][j]);
        }
        printf("\n");
    }
}

double** mult(double** m1, int r1, int c1, double** m2, int r2, int c2){
    int i, j, k, somma;
    double** ret;
    if(m1==NULL || m2 ==NULL){
        printf("matrici non disponibile\n");
        return NULL;
    }
    if(c1!=r2){
        printf("impossibile effettuare il prodotto!!\n");
        return NULL;
    }
    ret = create(r1, c2);
    if(ret==NULL)
        return ret;

    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++) {
            somma=0;
            for (k = 0; k < c1; k++) {
                somma += m1[i][k]*m2[k][j];
            }
            ret[i][j]=somma;
        }
    return ret;
}

int main(int argc, char const *argv[]) {
    int r1, c1, r2, c2;
    double** a;
    double** b;
    double** c;

    printf("inserisci il numero di righe della matrice A >>");
    scanf("%d",&r1);
    printf("\ninserisci il numero di colonne della matrice A >>");
    scanf("%d",&c1);
    a = create(r1,c1);
    printf("\n\ninserisci gli elementi della matrice A >>\n");
    read(a, r1, c1);
    printf("Matrice A:\n");
    print(a, r1, c1);

    printf("\ninserisci il numero di righe della matrice B >>");
    scanf("%d",&r2);
    printf("\ninserisci il numero di colonne della matrice B >>");
    scanf("%d",&c2);
    b=create(r2,c2);
    printf("\n\ninserisci gli elementi della matrice B >>\n");
    read(b, r2, c2);
    printf("\n\nMatrice B:\n");
    print(b, r2, c2);

    c=mult(a, r1, c1, b, r2, c2);
    printf("\n\nA x B = C\n");
    print(c,r1,c2);
}
