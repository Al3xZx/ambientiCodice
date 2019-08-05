#include <stdio.h>
#define N 5
#define M 8

//1)  Verificare che un vettore sia composto da tutti numeri positivi e pari
void prima(int* vett){/*non è possibile usare come parametro il vettore perchè
                        essendo un passaggio per valore si andrebbe a copiare
                        tutto l'array e se questo ha dimensioni elevate
                        porterebbe inefficienza*/
    int i=0, verificato=1;
    //int n= sizeof(vett)/sizeof(int) ;
    //printf("l'array ha dimensione: %d\n", n);
    printf("primo elemento %d\n", *vett);
    for(i = 0; i < N; i++) {
        if (vett[i]%2!=0 || vett[i]<0){
            verificato=0;
            break;
        }
    }
    printf("1)  Verificare che un vettore sia composto da tutti numeri positivi e pari\n");
    if(verificato)
        printf("il vettore verifica le proprietà\n");
    else
        printf("il vettore non verifica le proprietà\n");
}

//2) Verificare se un numero x (letto da tastiera) e' presente in un vettore
void seconda(int* vett){
    int i=0, trovato=0;
    int x=0;
    printf("2) Verificare se un numero x (letto da tastiera) e' presente in un vettore\n");
    printf("inserire il numero da cercare >> ");
    scanf("%d", &x);
    for (i = 0; i < N; i++) {
        if(vett[i]==x){
            trovato=1;
            break;
        }
    }
    if(trovato)
        printf("il vettore contiene %d\n",x);
    else
        printf("il vettore non contiene %d\n",x);
}

//3) Contare le occorrenze del numero 5 in un vettore
void occorrenze(int* vett){
    printf("3) Contare le occorrenze del numero 5 in un vettore\n");
    int occorrenze=0, i=0;
    for (i = 0; i < N; i++)
        if(vett[i]==5)
            occorrenze++;
    printf("le occorrenze di 5 nel vettore sono %d\n", occorrenze);
}//occorrenze

//4) Verificare che tutti gli elementi di un vettore V1 siano presenti in un vettore V2
void elementiPresenti(int* V1, int* V2) {
    printf("4) Verificare che tutti gli elementi di un vettore V1 siano presenti in un vettore V2\n");
    int esiste=0, i=0, j=0;
    for(i=0; i<N; i++){
        esiste=0;
        for(j=0;j<M;j++){
            if(V1[i]==V2[j]){
                esiste=1;
                break;
            }
        }
        if(!esiste){
            printf("non tutti gli elementi di v1 sono v2\n");
            return;
        }
    }
    printf("tutti gli elementi di v1 sono v2\n");
}//elementiPresenti

int main(){
    int vett[N]={5,2,5,4,22};
    int vett2[M]={5,2,35,4,22,8,6,12};
    prima(vett);
    seconda(vett);
    occorrenze(vett);
    elementiPresenti(vett, vett2);
}
