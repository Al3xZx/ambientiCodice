/*Esercizio 3 (12 punti)
Realizzare un programma C che, utilizzando le System Call di Linux, sommi i numeri
in valore assoluto < 15 e quelli maggiori  uguale a 15 contenuti nel file “Numeri.dat”,
contenente k numeri interi.
Il processo principale dovrà creare due pipe e quindi 2 processi figli Fa e Fb.
Il padre leggerà un numero dal file “Dati” e, se è minore in valore assoluto di 15,
lo scriverà sulla pipe che lo collega a Fa, altrimenti lo manderà a Fb. Tutto ciò sarà
ripetuto fino alla fine del file, quindi il padre manderà un numero speciale (magari 0)
per indicare ai figli che non ci sono più numeri.
Fa sommerà tutti numeri ricevuti dal padre e scriverà il risultato all’inizio del file “posA”,
già esistente.  Fb farà lo stesso e lo scriverà alla fine del file “posB”.
(Suggerimento: utilizzare lseek per posizionarsi all’inizio o alla fine del file
prima di scrivervi i risultati.)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void codiceFiglio(int, int[][2]);
void stampaFile(int fd);

int main(int argc, char const *argv[]) { /*fa->id=0; fb->id=1*/
    int id, pid, fd, i,status;
    int pd[2][2];
    fd = open("Numeri.dat",O_RDONLY);
    if (fd<0) {
        printf("errore file\n");
        exit(-1);
    }
    printf("il file Numeri.dat contiene:\n");
    stampaFile(fd);
    for (i = 0; i < 2; i++) {
        if (pipe(pd[i])<0) {
            printf("errore pipe\n");
            exit(-1);
        }
    }
    pid=getpid();
    for (i = 0; i < 2; i++) {
        if (pid>0) {
            id=i;
            pid=fork();
        }
    }
    if (pid<0) {
        printf("errore creazione processo\n");
        exit(-1);
    } else if (pid==0) {
        codiceFiglio(id,pd);
    } else {/* codice padre */
        int k,num,tappo;

        k=lseek(fd,0,SEEK_END)/sizeof(int);
        i=0;tappo=0;
        lseek(fd,0,SEEK_SET);
        while(i<k){
            read(fd,&num,sizeof(int));
            if (num<0) {
                if((num*-1)<15)
                    write(pd[0][1],&num,sizeof(int));
                else
                    write(pd[1][1],&num,sizeof(int));
            }else{
                if(num<15)
                    write(pd[0][1],&num,sizeof(int));
                else
                    write(pd[1][1],&num,sizeof(int));
            }
            i++;
        }
        write(pd[0][1],&tappo,sizeof(int));
        wait(&status);
        write(pd[1][1],&tappo,sizeof(int));
        wait(&status);
    }
    close(fd);
    return 0;
}

void codiceFiglio(int id, int pd[][2]){
    int somma,numero,fdA,fdB;
    read(pd[id][0],&numero,sizeof(int));
    somma=0;
    while(numero!=0){
        somma+=numero;
        read(pd[id][0],&numero,sizeof(int));
    }
    if (id==0) {
        fdA=open("posA",O_RDWR);
        lseek(fdA,0,SEEK_SET);
        printf("scrivo all'inizio di posA %d\n",somma);
        write(fdA,&somma,sizeof(int));
        printf("il file posA contiene:\n");
        stampaFile(fdA);
        close(fdA);
    } else {
        fdB=open("posB",O_RDWR);
        lseek(fdB,0,SEEK_END);
        printf("scrivo alla fine di posB %d\n",somma);
        write(fdB,&somma,sizeof(int));
        printf("il file posB contiene:\n");
        stampaFile(fdB);
        close(fdB);
    }
}

void stampaFile(int fd){
    int k,tmp,l;
    l=lseek(fd,0,SEEK_END)/sizeof(int);
    lseek(fd,0,SEEK_SET);
    k=0;
    while(k<l){
        read(fd,&tmp,sizeof(int));
        printf("%d\n", tmp);
        k++;
    }
}
