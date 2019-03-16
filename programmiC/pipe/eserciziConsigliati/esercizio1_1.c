#include <stdio.h>
/*#include <sys/type.h>*/
#include <unistd.h>/*per le system call posix*/
/*#include <sys/wait.h>*/
#include <stdlib.h>
#include <math.h>


/*1.1) Il padre legge un intero lo passa al figlio che fa il quadrato del numero,
    lo restituisce al padre che lo  stampa su schermo*/
int main(int argc, char const *argv[]) {
    int pid, status, pidChild;

    int pd1[2];/*pipe scrittura padre lettura figlio*/
    int pd2[2];/*pipe lettura padre scrittura figlio*/

    int buffer;
    int numero;
    int numeroQ;
    
    printf("inserire il numero da elevare a 2 >> ");
    scanf("%d",&numero);

    /*creo la pipe*/
    if(pipe(pd1)==-1 || pipe(pd2)==-1){
        printf("impossibile creare le pipe\n");
        exit(-1);
    }
    pid = fork();
    switch (pid) {
        case -1:
            printf("impossibile creare il nuovo processo\n");
            exit(-1);
            break;
        case 0: /*codice del figlio*/
            read(pd1[0],&buffer,sizeof(int));
            printf("mio padre %d mi ha mandato il numero %d\n", getppid(), buffer);
            buffer *= buffer;
            /*buffer=pow(buffer,2); non lo esegue????*/
            /*sleep(2);/*pausa di 2 secondi*/
            write(pd2[1],&buffer,sizeof(int));
            break;
        default: /*codice padre*/
            write(pd1[1],&numero,sizeof(int));
            pidChild=wait(&status);
            read(pd2[0],&numeroQ,sizeof(int));
            printf("mio figlio %d mi ha mandato il numero %d ^ 2 = "
            "%d\n",pidChild, numero, numeroQ);
            break;
    }
    return 0;
}
