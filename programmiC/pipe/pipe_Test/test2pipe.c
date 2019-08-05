#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void stampaVettore(int*, int);
void leggiVettorre(int*, int);
int* allocaVettore(int);
/*il padre legge un array lo passa al figlio che lo stampa su schermo*/
int main(int argc, char const *argv[]) {
    int pid, status, pidChild, ris;
    int numeroElementi;
    int* vett;
    int* buff;
    int pd[2];
    ris=pipe(pd);
    if (ris==-1) {
        printf("%s\n", "errore nella creazione della pipe");
        exit(-1);
    }

    printf("inserire il numero di elementi che costituirà l'array >>");
    scanf("%d",&numeroElementi);
    vett=allocaVettore(numeroElementi);
    buff=allocaVettore(numeroElementi);

    pid=fork();
    if (pid==-1) {
        printf("%s\n", "errore nella creazione del processo!!");
    } else if (pid==0) {

        close(pd[1]);//chiudo la pipe in scrittura
        read(pd[0],buff,numeroElementi*sizeof(int));
        printf("sono il processo %d il processo %d mia ha mandato: \n",getpid(),getppid());
        stampaVettore(buff,numeroElementi);
        free(buff);
    } else {
        close(pd[0]);
        leggiVettorre(vett,numeroElementi);
        write(pd[1],vett,sizeof(int)*numeroElementi);
        pidChild=wait(&status);
        printf("il processo %d ha terminato\n",pidChild);
        free(vett);
    }
    return 0;
}

void stampaVettore(int* v, int n){
    int i;
    printf("[ ");
    for (i = 0; i < n; i++) {
        if (i < n-1) {
            printf("%d, ", v[i]);
        } else {
            printf("%d ]\n", v[i]);
        }
    }
}

void leggiVettorre(int* v, int n){
     int i;
     for (i = 0; i < n; i++) {
         printf("inserire l'elemento %d >>",i);
         scanf("%d",&v[i]);
     }
}

int* allocaVettore(int n){
    int* ret = (int*) malloc(n*sizeof(int));
    if(ret==NULL){
        printf("%s\n", "ERRORE!! memoria non disponibile");
        exit(-1);
    }
    return ret;
}
