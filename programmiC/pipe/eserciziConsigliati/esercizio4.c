/*Il padre legge un vettore da tastiera, quindi crea 2 figli Fpos e Fneg.
Il padre passa i numeri positivi a Fpos e i negativi a Fneg.

Fpos calcola la media dei numeri positivi e la ritorna al padre che la stampa.

Fneg crea un nipote Fnip, gli passa i numeri negativi e Fnip calcola il minimo
dei numeri negativi e lo ritorna a Fneg che lo ritorna al padre che lo stampa.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define FPOS 0
#define FNEG 1

void leggiVettore(int*, int);
void codiceFpos(int[4][2]);/*le matrici sono passate sempre come riferimento
                             ma il compilatore ha la necessita di sapere il numero di colonne
                             in questo caso è 2(il numero di righe in questo caso 4 è facoltativo)
                             a meno che non si utilizzi l'allocazione dinamica*/
void codiceFneg(int[4][2]);
void stampaVettore(int* v, int n);
int main(int argc, char const *argv[]) {
    int pid, i,tappo, status;
    float mediaPos;
    int minNeg;
    int id; /*id == 0 Fpos, id == 1 Fneg*/
    int numeroElementi;
    int* vett;
    int pd[4][2]; /*0 p->Fpos, 1 Fpos -> p, 2 p->Fneg, 3 Fneg->p*/

    for(i=0;i<4;i++)
        if (pipe(pd[i])==-1) {
            printf("%s\n", "ERRORE creazione pipe!!");
            exit(-1);
        }

    printf("inserire numero elementi del vettore > ");
    scanf("%d",&numeroElementi);
    vett=(int*)malloc(numeroElementi*sizeof(int));
    if (vett==NULL) {
        printf("ERRORE memoria non disponibile\n");
        exit(-1);
    }
    leggiVettore(vett, numeroElementi);
    printf("%s\n", "il vettore inserito è: ");
    stampaVettore(vett,numeroElementi);
    pid=getpid();
    for(i=0;i<2;i++)
        if (pid>0) {
            id=i;
            pid=fork();
        }
    if (pid==-1) {
        printf("%s\n", "ERRORE creazione processo");
        exit(-1);
    } else if (pid==0) {
        if (id==FPOS) {
            codiceFpos(pd);
        } else if (id==FNEG) {
            codiceFneg(pd);
        }
    } else {
        close(pd[0][0]); close(pd[2][0]);
        close(pd[1][1]); close(pd[3][1]);
        for(i=0;i<numeroElementi;i++){
            if(vett[i]>0){
                write(pd[0][1],&vett[i],sizeof(int));
                printf("ho inviato %d a Fpos\n",vett[i]);
            }else if(vett[i]<0){

                write(pd[2][1],&vett[i],sizeof(int));
                printf("ho inviato %d a Fneg\n",vett[i]);
            }
        }
        tappo=0;
        write(pd[0][1],&tappo,sizeof(int));
        printf("ho inviato %d a Fpos\n",tappo);
        write(pd[2][1],&tappo,sizeof(int));
        printf("ho inviato %d a Fneg\n",tappo);
        /*for (i = 0; i < 2; i++)
            wait(&status);*/ //facoltativo perchè read e write sono bloccanti
        read(pd[1][0],&mediaPos,sizeof(float));
        read(pd[3][0],&minNeg,sizeof(int));
        printf("la media dei positivi è %.2f il minimo tra i negativi è %d \n",mediaPos,minNeg);
        printf("%s\n", "libero memoria...");
        free(vett);
    }
    return 0;
}//main

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
void leggiVettore(int* v, int n){
    int i;
    for (i = 0; i < n; i++) {
        printf("inserire l'elemento %d >> ", i);
        scanf("%d", &v[i]);
    }
}//leggiVettore

/*Fpos calcola la media dei numeri positivi e la ritorna al padre che la stampa.*/
void codiceFpos(int pd[4][2]){
    float ret;
    int c, elemento,somma;
    close(pd[0][1]);close(pd[1][0]);

    read(pd[0][0],&elemento,sizeof(int));
    printf("sono Fpos ho ricevuto %d da papà\n", elemento);
    while(elemento!=0){
        somma+=elemento;
        c++;
        read(pd[0][0],&elemento,sizeof(int));
        printf("sono Fpos ho ricevuto %d da papà\n", elemento);
    }
    ret=(float)somma/c;
    write(pd[1][1],&ret,sizeof(float));
}//codiceFpos

/*Fneg crea un nipote Fnip, gli passa i numeri negativi e Fnip calcola il minimo
dei numeri negativi e lo ritorna a Fneg che lo ritorna al padre che lo stampa.*/
void codiceFneg(int pd[4][2]){
    int pidNip, i;
    int elemento, buff, status, min;
    int attuale, ret;
    int pdNip[2][2];// 0 Fneg-> Nip, 1 Nip -> Fneg
    for (i = 0; i < 2; i++) {
        if (pipe(pdNip[i])==-1) {
            printf("%s\n", "ERRORE creazione pipe");
            exit(-1);
        }
    }
    pidNip=fork();
    if (pidNip==-1) {
        printf("%s\n", "ERRORE creazione processo");
        exit(-1);
    } else if (pidNip==0) {//codiceNipote

        close(pdNip[1][0]);close(pdNip[0][1]);
        read(pdNip[0][0],&attuale,sizeof(int));
        ret=attuale;
        while(attuale != 0){
            if(attuale < ret)
                ret=attuale;
            read(pdNip[0][0],&attuale,sizeof(int));
        }
        write(pdNip[1][1],&ret,sizeof(int));
    } else {//codice Fneg
        close(pd[2][1]);close(pd[3][0]);
        close(pdNip[0][0]);close(pdNip[1][1]);

        read(pd[2][0],&elemento,sizeof(int));
        printf("sono Fneg ho ricevuto %d da papà\n", elemento);
        while(elemento!=0){
            write(pdNip[0][1],&elemento,sizeof(int));
            read(pd[2][0],&elemento,sizeof(int));
            printf("sono Fneg ho ricevuto %d da papà\n", elemento);
        }
        write(pdNip[0][1],&elemento,sizeof(int));//invio elemento tappo
        //wait(&status);//facoltativo perchè read e write sono bloccanti
        read(pdNip[1][0],&min,sizeof(int));
        write(pd[3][1],&min,sizeof(int));
    }
}//codiceFneg
