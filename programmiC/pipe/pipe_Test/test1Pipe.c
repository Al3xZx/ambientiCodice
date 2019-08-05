#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*Il padre legge un intero da tastiera lo passa al figlio che lo stampa*/

int main(int argc, char const *argv[]) {
    int pid, status, x, buff, pidChild, ris;
    int pd[2];
    ris=pipe(pd);
    if (ris==-1) {
        printf("non è stato possibile creare la pipe!\n");
        exit(-1);
    }
    pid=fork();
    if (pid==-1) {
        printf("%s\n", "non è stato possibile creare un nuovo processo");
        exit(-1);
    } else if (pid==0) {
        close(pd[1]);
        read(pd[0],&buff,sizeof(int));
        printf("sono il processo %d il processo %d mi ha mandato il numero %d\n",getpid(),getppid(),buff);
    } else {
        close(pd[0]);
        printf("inserire il numero da stampare >> ");
        scanf("%d",&x);
        write(pd[1],&x,sizeof(int));
        pidChild=wait(&status);
        printf("mio figlio %d ha terminato l'esecuzione\n", pidChild);
    }
    return 0;
}
