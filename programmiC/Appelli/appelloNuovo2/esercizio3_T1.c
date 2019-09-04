/*Realizzare un programma C che, utilizzando le System Call di Linux,
e sommi in parallelo il contenuto di un file ‘ricavi.txt’.
Il processo principale dovrà creare una (o più) pipe e quindi N processi figli
F1, F2, ., .FN. Il primo figlio conterà le occorrenze nella porzione di file dalla
posizione 0 alla posizione L/N – 1, il secondo dalla posizione L/N alla posizione
2* (L/N) -1 e così via. Quindi i figli invieranno al padre i risultati parziali
tramite la pipe e il genitore provvederà a calcolare il totale e stamperà in output la somma totale.
(Suggerimento: utilizzare lseek per spostarsi nel file.)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N 2
void codiceFiglio(int id,int inizio,int fine,int fd,int pd[][2]);
int main(int argc, char const *argv[]) {
    int pid, id, i, fd, l;
    int pd[N][2];
    fd=open("ricavi.bin",O_RDONLY,0666);
    if(fd<0){
        printf("ERRORE apertura file\n");
        exit(-1);
    }
    for(i=0;i<N;i++){
        if(pipe(pd[i])<0){
            printf("ERRORE creazione pipe\n");
            exit(-1);
        }
    }
    l=lseek(fd,0,SEEK_END)/sizeof(int);
    pid=getpid();
    for(i=0;i<N;i++){
        if(pid>0){
            id=i;
            pid=fork();
        }
    }
    if (pid<0) {
        printf("ERRORE creazione processo\n");
        exit(-1);
    } else if (pid==0) {
        codiceFiglio(id,id*(l/N),((id+1)*(l/N))-1,fd,pd);
    } else {
        /* code padre*/
        int i, somma, tmp;
        somma=0;
        for (i = 0; i < N; i++) {
            read(pd[i][0],&tmp,sizeof(int));
            printf("il processo %d mi ha mandato %d\n",i,tmp);
            somma+=tmp;
        }
        printf("il totale è: %d\n", somma);
    }
    close(fd);
    return 0;
}
void codiceFiglio(int id,int inizio,int fine,int fd,int pd [][2]){
    int somma,tmp, k;
    k=0;
    somma=0;
    while(k<=(fine-inizio)){
        lseek(fd,(inizio+k)*sizeof(int),SEEK_SET);
        read(fd,&tmp,sizeof(int));
        printf("%d\n",tmp);
        somma+=tmp;
        k++;
    }
    write(pd[id][1],&somma,sizeof(int));
}
