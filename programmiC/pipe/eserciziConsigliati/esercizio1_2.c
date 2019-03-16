#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
1.2) Il padre legge un array lo passa al figlio che fa il quadrato dei numeri,
     lo restituisce al padre che lo  stampa su schermo.
*/
void printVect(int* v, int dim);
void readVect(int* v, int dim);
int main(int argc, char const *argv[]) {
    int i;
    int pid, status, pidChild;
    int* v;
    int* newV;
    int* buffer;
    int pd1[2];/*scrittura padre lettura figlio*/
    int pd2[2];/*lettura padre scrittura figlio*/
    int dim;

    /*leggo il vettore da tastiera*/
    printf("inserire il numero di elementi >> ");
    scanf("%d",&dim);
    v=(int*) malloc(dim*sizeof(int));
    newV=(int*) malloc(dim*sizeof(int));
    buffer=(int*) malloc(dim*sizeof(int));
    if(v==NULL||newV==NULL||buffer==NULL){
        printf("memoria insufficiente\n");
        exit(-1);
    }
    readVect(v, dim);
    printf("hai inserito il vettore:");
    printVect(v,dim);

    /*creo le pipe*/
    if(pipe(pd1)==-1||pipe(pd2)==-1){
        printf("impossibile creare le pipe\n");
        /*devo fare le free delle tre locazioni*/
        exit(-1);
    }

    pid=fork();
    switch (pid) {
        case -1:
            printf("impossibile creare il nuovo processo\n");
            /*de allocare la memoria*/
            exit(-1);
            break;
        case 0:/*codice figlio*/
            /*read e write come secondo parametro necessitano di un puntatore dunque
            essendo buffer v e newV già dei puntatori non si DEVE anteporre la & */
            read(pd1[0],buffer,dim*sizeof(int));
            printf("mio padre %d mi ha mandato il vettore:\n", getppid());
            /*printVect(buffer,dim);*/
            for (i = 0; i < dim; i++) {
                buffer[i]*=buffer[i];
            }
            write(pd2[1],buffer,dim*sizeof(int));
            break;
        default:
            write(pd1[1],v,dim*sizeof(int));
            pidChild=wait(&status);
            read(pd2[0],newV,dim*sizeof(int));
            printf("mio filglio %d mi ha mandato il vettore elevato al quadrati\n",pidChild);
            /*printVect(newV,dim);*/
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

void readVect(int* v, int dim){
    int i;
    for (i = 0; i < dim; i++) {
        printf("inserire l'elemento v[%d] >>", i);
        scanf("%d",&v[i]);/*quando uso la notazione posiziona devo anteporre la &
                            perchè V[i] è un valore e scanf vuole il puntatore
                            se uso direttamente l'aritmetica dei puntatori andrò
                            a scrivere banalmente v+i*/
    }
}
