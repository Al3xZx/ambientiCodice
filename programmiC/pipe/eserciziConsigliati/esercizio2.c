#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*2) Il padre legge un vettore da tastiera, quindi crea 2 figli F1 e F2,
   manda i numeri multipli di 2  al figlio F1, i multipli di 3 a F2.
   F1 calcola la media dei multipli di 2, mentre F2 calcola il massimo dei multipli di 3.
   Per semplicità si suppone che non esiste lo 0 fra i numeri letti.
*/

void printVect(int* v, int dim);
void readSendVect(int* v, int dim, int** pd);

int main(int argc, char const *argv[]) {
    int i;
    int pid, status;
    int** pd;/*sono 4 pipe descriptor 2 per ogni coppia padre figlio*/
    int idFiglio;/*tale valore varia successivamente alla fork*/
    int dim;
    int mul2; float mediaMul2, sommaMul2, cont;
    int maxMul3, mul3;
    int* v;
    float resF1; int resF2,tappo;

    /*leggo dim e vettore da tastiera*/
    printf("inserire la dimensione del vettore >> ");
    scanf("%d",&dim);
    v=(int*)malloc(dim*sizeof(int));
    if(v==NULL){
        printf("memoria insufficiente\n");
        exit(-1);
    }
     /*creo le pipe*/
    pd=(int**)malloc(4*sizeof(int*));
    if(pd==NULL){
        printf("memoria insufficiente\n");
        exit(-1);
    }
    for(i=0;i<4;i++){
        pd[i]=(int*)malloc(2*sizeof(int));
        if(pd[i]==NULL || pipe(pd[i])==-1){
            printf("errore nella creazione della pipe %d\n", i);
            exit(-1);
        }
    }
    /*creo i figli*/
    pid = getpid();/*inizializzo pid con il pid del padre*/
    for(i=0;i<2;i++){
        if(pid > 0){
            idFiglio=i;
            pid = fork();
        }
    }
    switch (pid) {
        case -1:
            printf("errore nella creazione del processo con id %d\n",idFiglio );
            exit(-1);
            break;
        case 0:
            if(idFiglio==0){/*codice figlio calcolo multipli di 2 leggo pd[0] scrivo pd[1]*/
                sommaMul2=0;
                cont=0;
                read(pd[0][0],&mul2,sizeof(int));
                while(mul2!=0){
                    printf("sono F1 e ho letto %d\n",mul2);
                    sommaMul2+=mul2;
                    cont++;
                    read(pd[0][0],&mul2,sizeof(int));
                }
                printf("sono F1 e ho letto %d\n",mul2);
                mediaMul2=sommaMul2/cont;
                write(pd[1][1],&mediaMul2,sizeof(float));

            }else{/*codice figlio calcolo multipli di 3 leggo pd[2] scrivo pd[3]*/
                maxMul3=0;
                read(pd[2][0],&mul3,sizeof(int));
                while(mul3!=0){
                    if(mul3>maxMul3){
                        printf("sono F2 e ho letto %d\n",mul3);
                        maxMul3=mul3;
                    }
                    read(pd[2][0],&mul3,sizeof(int));
                }
                printf("sono F2 e ho letto %d\n",mul3);
                write(pd[3][1],&maxMul3, sizeof(int));
            }
            break;
        default:/*codice padre*/
            readSendVect(v,dim,pd);
            /*invio il tappo*/
            tappo=0;
            write(pd[0][1],&tappo,sizeof(int));/*tappo per f1*/
            write(pd[2][1],&tappo,sizeof(int));/*tappo per f2*/
            /*wait dei figli*/
            printf("aspetto che i figli terminano\n");
            for(i=0;i<2;i++)
                wait(&status);
            /*lettura dei risultati*/
            read(pd[1][0],&resF1,sizeof(float));
            read(pd[3][0],&resF2,sizeof(int));
            printf("la media dei multipli di 2 è %f\n",resF1);
            printf("la massimo tra multipli di 3 è %d\n",resF2);
            break;
    }




    return 0;
}

void printVect(int* v, int dim){
    int i;
    printf("[ ");
    for (i = 0; i < dim; i++) {
        if(i!=dim-1)
            printf("%d, ", v[i]);
        else
            printf("%d ]\n", v[i]);
    }
}

void readSendVect(int* v, int dim, int** pd){
    int i;
    for (i = 0; i < dim; i++) {
        printf("inserire l'elemento v[%d] >>", i);
        scanf("%d",&v[i]);
        if(v[i]%2==0)
            write(pd[0][1],&v[i],sizeof(int));
        else if(v[i]%3==0)
            write(pd[2][1],&v[i],sizeof(int));
    }
}
