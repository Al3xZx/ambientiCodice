/*5) Il padre legge un vettore da tastiera lo partiziona in N parti in modo tale che
    N figli leggano la partizione i quali effettueranno la somma degli elementi
    riguardanti la loro partizione e la invieranno al padre che sommerà le N somme
    inviate dai figli e stamperà su schermo tale valore.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 4
#define DIM 2094599

void readVect(int*);
void codiceFiglio(int*,int*,int*);

int main(int argc, char const *argv[]) {
    int pid, status, pidChild;
    int v[DIM];
    int pdPF[N][2];/*padre scrive figlio legge*/
    int pdFP[N][2];/*figlio scrive padre legge*/
    /*ERRORE!!!!! int somme[N];VA USATA LA PIPE pfFP*/
    int sumTot, sum;
    int i;
    int id;
    int passo, figlio;
    int range[N][2];

    /*TODO far dare DIM e N all'uetente*/
    /*leggo il vettore
    readVect(v);*/
    /*genero un vettore di DIM numeri casuali*/
    for (i = 0; i < DIM; i++) {
        v[i]=rand()%100;
    }

    /*creo le pipe*/
    for(i=0;i<N;i++)
        if(pipe(pdPF[i])==-1||pipe(pdFP[i])==-1){
            printf("impossibile creare le pipe\n");
            exit(-1);
        }

    /*creo i processi*/
    pid=getpid();
    for(i=0;i<N;i++)
        if(pid>0){
            id=i;
            pid = fork();
        }

    switch (pid) {
        case -1:
            printf("impossibile creare il processo %d\n", id);
            exit(-1);
            break;
        case 0:
            codiceFiglio(v,pdPF[id],pdFP[id]);
            break;
        default:
            /*readVect(v);ERRORE!!!!! IL VETTORE LO DEVO LEGGERE PRIMA DI CREARE I FILGLI*/
            /*assegno le partizioni ai processi*/
            figlio=0;
            passo=DIM/N;
            for(i=0;i<DIM;i+=passo){
                if(figlio<N-1){
                    range[figlio][0]=i;
                    range[figlio][1]=passo+i;
                    write(pdPF[figlio][1],range[figlio],2*sizeof(int));
                    printf("sono %d ho inviato l'intervallo [%d,%d)\n",getpid(), range[figlio][0],range[figlio][1]);
                    figlio++;
                }else{
                    range[figlio][0]=i;
                    range[figlio][1]=DIM;
                    write(pdPF[figlio][1],range[figlio],2*sizeof(int));
                    printf("sono %d ho inviato l'intervallo [%d,%d)\n",getpid(), range[figlio][0],range[figlio][1]);
                    break;
                }
            }
            /*aspetto che terminino*/
            printf("aspetto che tutti terminino.....\n");
            for (i = 0; i < N; i++){
                pidChild=wait(&status);
                printf("%d ha terminato\n",pidChild);
            }
            /*combino i risultati dei figli*/
            sumTot=0;
            for (i = 0; i < N; i++){
                read(pdFP[i][0],&sum,sizeof(int));
                printf("il figlio %d mi ha mandato %d\n",i,sum);
                sumTot+=sum;
            }
            printf("la somma totale è: %d\n", sumTot);
    }


    return 0;
}

void codiceFiglio(int* v,int* pdPF,int* pdFP){
    int* inter;
    int i, somma;
    /*ERRORE!!!! inter dopo la dichiarazione va definita una allocazione
                 altrimenti la read dove mette l'intervallo???????*/
    inter=(int*)malloc(2*sizeof(int));
    read(pdPF[0],inter,2*sizeof(int));
    printf("sono %d e sto eseguendo ho ricevuto l'intervallo [%d,%d)\n",getpid(), inter[0],inter[1]);
    somma=0;
    for(i=inter[0];i<inter[1];i++)
        somma+=v[i];
    write(pdFP[1],&somma,sizeof(int));
}

void readVect(int* v){
    int i;
    for (i = 0; i < DIM; i++) {
        printf("inserire l'elemento v[%d] >>", i);
        scanf("%d",&v[i]);/*quando uso la notazione posiziona devo anteporre la &
                            perchè V[i] è un valore e scanf vuole il puntatore
                            se uso direttamente l'aritmetica dei puntatori andrò
                            a scrivere banalmente v+i*/
    }
}
