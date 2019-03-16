#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
/*DA RIFAREE*/
#define N 2
void codiceFiglio(int,int*, int*, int);
int main(int argc, char const *argv[]) {
    int pid, status, pidChild, id;
    int pdPF[N][2];
    int pdFP[N][2];
    int fd;
    int i, numeroCaratteri, tmp, occorrenzeDiA;

    /*apro il file*/
    fd=open("lettera.txt",O_CREAT|O_RDONLY,0644);
    if(fd<0){
        printf("errore di apertura del file\n");
        exit(-1);
    }

    /*creo le pipe*/
    for (i = 0; i < N; i++) {
        if(pipe(pdFP[i])==-1|pipe(pdPF[i])==-1){
            printf("errore nella creazione delle pipe\n");
            exit(-1);
        }
    }

    /*creo i figli*/
    pid=getpid();
    for (i = 0; i < N; i++) {
        if(pid>0){
            id =i;
            pid=fork();
        }
    }

    switch(pid){
        case -1:
            printf("errore nella creazione del figlio %d\n",id);
            exit(-1);
            break;
        case 0:
            codiceFiglio(id,pdPF[id],pdFP[id], fd);
        default:

            numeroCaratteri=lseek(fd,0,SEEK_END)/sizeof(char);
            printf("il numero di caratteri del file è %d\n",numeroCaratteri);
            for (i = 0; i < N; i++)
                write(pdPF[i][1],&numeroCaratteri,sizeof(int));
            for (i = 0; i < N; i++)
                wait(&status);
            occorrenzeDiA=0;
            for (i = 0; i < N; i++){
                read(pdFP[i][0],&tmp,sizeof(int));
                occorrenzeDiA+=tmp;
            }
            printf("il numero di a è %d\n",occorrenzeDiA);
    }
    return 0;
}
void codiceFiglio(int id,int* pdPF, int* pdFP, int fd){
    int i, numeroCaratteri, posizione, sum,testina;
    char c;
    read(pdPF[0],&numeroCaratteri,sizeof(int));
    posizione=(numeroCaratteri/N)*id;

    testina = lseek(fd,posizione*sizeof(char),SEEK_SET);
    printf("sono il figlio %d e sono posizionato in %d, %d\n",id,posizione,testina);
    sum=0;
    while(posizione<numeroCaratteri*(id+1)){
        read(fd,&c,sizeof(char));
        printf("sono %d e ho letto %c\n",id,c);
        if(c == 'a')
            sum++;
        posizione++;
    }
    write(pdFP[1],&sum,sizeof(int));
}
