/*3( Il padre legge un vettore da tastiera, quindi crea N figli,
 ogni figlio calcola la media del multiplo (considerare multipli di 2, 3 e 4, ......,N;
 F1 % 2, F2 % 3, F3 % 4,.........,FN % N)*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 4
void codiceFiglio(int, int*, int*);
void stampaMedie(float*);
void readSendVect(int*, int, int[N][2]);

int main(int argc, char const *argv[]) {
    int pid, status;
    int pdPF[N][2];/*pipe scrive padre legge figlio*/
    int pdFP[N][2];/*pipe scrive figlio legge padre*/
    float mediaP[N];
    int id;
    int* v;
    int dim,i;
    int tappo, val;

    /*leggo dim da tastiera*/
    printf("inserire la dimensione del vettore >> ");
    scanf("%d",&dim);
    v=(int*)malloc(dim*sizeof(int));
    if(v==NULL){
        printf("memoria insufficiente\n");
        exit(-1);
    }
    /*creo le pipe*/
    for(i=0;i<N;i++){
        if(pipe(pdPF[i])==-1|| pipe(pdFP[i])==-1){
            printf("impossibile creare la pipe %d\n",i);
            exit(-1);
        }
    }
    /*creo i figli*/
    pid=getpid();
    for(i=0;i<N;i++){
        if(pid>0){
            id=i;
            pid=fork();
        }
    }

    switch (pid) {
        case -1:
            printf("impossibile creare il figlio %d \n",id);
            break;
        case 0:
            codiceFiglio(id,pdPF[id],pdFP[id]);
            break;
        default:
            readSendVect(v,dim,pdPF);
            /*invio segnale di arresto*/
            tappo=0;
            for(i = 0; i < N; i++)
                write(pdPF[i][1],&tappo,sizeof(int));
            /*aspetto che tutti terminino*/
            for(i = 0; i < N; i++)
                wait(&status);
            for(i = 0; i < N; i++)
                read(pdFP[i][0],&mediaP[i],sizeof(float));
            stampaMedie(mediaP);

    }
    free(v);
    return 0;
}
void readSendVect(int* v, int dim, int pd[N][2]){
    int i, j;
    for (i = 0; i < dim; i++) {
        printf("inserire l'elemento v[%d] != 0 >>", i);
        scanf("%d",&v[i]);
        if(v[i]==0){
            printf("hai inserito 0 riprovare\n");
            i--;
            continue;
        }
        for(j=0;j<N;j++)
            if(v[i]%(j+2)==0)
                write(pd[j][1],&v[i],sizeof(int));
    }
}

void stampaMedie(float* v){
    int i;
    for(i=0;i<N;i++)
        printf("#la media dei multipli di %d è %3.2f\n",i+2,v[i]);
}

void codiceFiglio(int id,int* pdPF,int* pdFP){
    int val;
    float mediaF, somma, cont;
    read(pdPF[0],&val,sizeof(int));
    somma=0;
    cont=0;
    mediaF=0;
    while(val!=0){
        somma+=val;
        cont++;
        read(pdPF[0],&val,sizeof(int));
    }
    if(cont>0)
        mediaF=somma/cont;
    write(pdFP[1],&mediaF,sizeof(float));
}
