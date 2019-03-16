#include <stdio.h>
#include <stdlib.h>
typedef enum{false, true} boolean;

float** create(int, int);
void read(float**, int, int);
void print(float**, int, int);
boolean trova_proprieta(float**, int, int, int*);
boolean verifica(float**, int, int, int, int );

float** create(int r, int c){
    int i,k;
    float** m= (float**)malloc(r*sizeof(float*));
    if(m==NULL){
        printf("memoria insufficiente\n");
        return NULL;
    }
    for(i=0;i<r;i++){
        m[i]=(float*)malloc(c*sizeof(float));
        if(m[i]==NULL){
            printf("memoria insufficiente\n");
            for(k=0;k<i;k++)
                free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}

void read(float** m, int r, int c){
    int i,j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("inserire l'elemento [%d, %d] >> ", i,j);
            scanf("%f",&m[i][j]);
        }
    }
}

void print(float** m, int r, int c){
    int i,j;
    for (i = 0; i < r; i++) {
        printf("| ");
        for (j = 0; j < c; j++) {
            if(j!= c-1)
                printf("%3.2f, ", m[i][j]);
            else
                printf("%3.2f |", m[i][j]);
        }
        printf("\n");
    }
}

boolean trova_proprieta(float** m, int r, int c, int* nR){
    int i, j, n, s;
    n=0;
    for (i = 0; i < r; i++) {
        s=0;
        for (j = 0; j < c; j++) {
            s+=m[i][j];
        }
        if(verifica(m,r,c,i,s))
            n++;
    }
    *nR=n;
    if(n>0)
        return true;
    return false;
}

boolean verifica(float** m, int r, int c, int riga, int somma){
    int i,j;
    for (i = 0; i < r; i++)
        if(i!=riga)
            for (j = 0; j < c; j++)
                if((5*m[i][j])==somma){
                    printf("elemento [%d, %d], riga %d\n",i,j, riga);
                    return true;
                }
    return false;
}

int main(int argc, char const *argv[]) {
    int r, c, n, i;
    int* pn;
    float** m;
    n=0;
    printf("inserire il numero di righe >> ");
    scanf("%d",&r);
    printf("inserire il numero di colonne >> ");
    scanf("%d",&c);
    m=create(r,c);
    if(m==NULL)
        exit(-1);
    printf("inserire i valori degli elementi\n");
    read(m,r,c);
    printf("la matrice inserita è:\n");
    print(m,r,c);
    if(trova_proprieta(m,r,c,&n))
        printf("il numero di righe che verificano la proprietà è %d\n",n);
    else
        printf("il numero di righe che verificano la proprietà è %d\n",n);
    for(i=0; i<r;i++)
        free(m[i]);
    free(m);
    return 0;
}
