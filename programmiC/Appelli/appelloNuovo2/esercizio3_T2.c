/*Esercizio 3, variante per esercitarsi (Programmazione system call, 12 punti)
Realizzare un programma C che, utilizzando le System Call di Linux, e conti
le occorrenze del voto 30 ed del voto 18
in un file binario ‘voti’. Il processo principale dovrà creare una (o più) pipe
e quindi 2 processi figli F18 e F30.  Quindi dovrà leggere al file i voti e se
il voto risulta essere 18, passarlo al figlio F18, mentre se il voto risulta F30
dovrà passarlo al figlio F30. Il primo figlio (F18) conterà le occorrenze del voto 18,
il secondo conterà le occorrenze del voto 30 e poi entrambi
ritorneranno il risultato al padre che li stamperà.
(Suggerimento: utilizzare lseek per spostarsi nel file.)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void codiceFiglio(int pd[4][2],int id);
int main(int argc, char const *argv[]) {
    int pid, id, i, fd, l;
    int pd[4][2];
    fd=open("voti.bin",O_RDONLY,0666);
    if(fd<0){
        printf("errore file\n");
        exit(-1);
    }
    for(i=0;i<4;i++){
        if (pipe(pd[i])<0) {
            printf("errore pipe\n");
            exit(-1);
        }
    }
    l=lseek(fd,0,SEEK_END)/sizeof(int);
    pid=getpid();
    for (i = 0; i < 2; i++) {
        if(pid>0){
            id=i;
            pid=fork();
        }
    }
    if (pid<0) {
        printf("ERRORE processo\n");
        exit(-1);
    } else if (pid==0) {
        codiceFiglio(pd,id);
    } else {/* codice padre*/
        int tappo,tot18,tot30;
        int vett[l];
        close(pd[0][0]);close(pd[1][0]);close(pd[2][1]);close(pd[3][1]);
        lseek(fd,0,SEEK_SET);
        read(fd,vett,l*sizeof(int));
        tappo=-1;
        for (i = 0; i < l; i++) {
            if(vett[i]==18)
                write(pd[0][1],&vett[i],sizeof(int));
            else if(vett[i]==30)
                write(pd[1][1],&vett[i],sizeof(int));
        }
        write(pd[0][1],&tappo,sizeof(int));
        write(pd[1][1],&tappo,sizeof(int));

        read(pd[2][0],&tot18,sizeof(int));
        read(pd[3][0],&tot30,sizeof(int));
        printf("il totale dei 18 è %d dei 30 è %d\n", tot18,tot30);
    }
    close(fd);
    return 0;
}
void codiceFiglio(int pd[4][2],int id){
    int c, tmp;
    c=0;
    close(pd[id][1]);close(pd[id+2][0]);
    read(pd[id][0],&tmp,sizeof(int));
    while(tmp!=-1){
        c++;
        read(pd[id][0],&tmp,sizeof(int));
    }
    write(pd[id+2][1],&c,sizeof(int));
}
