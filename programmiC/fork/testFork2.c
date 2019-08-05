#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*verifico se in seguito alla fork il figlio esce dal for o meno*/
int main(int argc, char const *argv[]) {
    int pid, i, id, status;
    pid=getpid(); 
    for(i=0;i<2;i++){
        if(pid>0){
            id=i;
            pid=fork();
        }
        if(pid == 0)printf("non creo il figlio del processo %d con pid %d\n",id, getpid());
    }

    if (pid==-1) {
        printf("ERRORE creazione processo\n");
        exit(-1);
    } else if (pid==0) {//codice figli
        printf("ciao sono il figlio %d il mio pid è %d\n",id, getpid());
    } else {
        for(i=0;i<2;i++){
            wait(&status);
        }
        printf("ciao sono il padre con pid %d\n",getpid());
    }

    return 0;
}
