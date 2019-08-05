#include <stdio.h>
#define N 5
//Verificare se un numero x (letto da tastiera) e' presente in un vettore
int trova(int*, int, int);//prototipo

int main(int argc, char const *argv[]) {
    int trovato, x;
    int v[N]={1,2,3,4,5};
    printf("inserisci il numero da cercare >>");
    scanf("%d",&x);
    trovato = trova(v,N,x);
    if (trovato)
        printf("l'elemento è presente\n");
    else
        printf("l'elemento NON è presente\n");
    return 0;
}
int trova(int* vett, int n, int x){
    int i;
    for (i = 0; i < n; i++)
        if(vett[i]==x)
            return 1;
    return 0;
}
