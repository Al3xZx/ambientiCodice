#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char const *argv[]) {
    int pid,status;
    printf("ciao a tutti!\n");
    pid=fork();
    switch (pid) {
        case -1:
        printf("%s\n", "errore nella creazione del processo");
        break;
        case 0://processo figlio
        printf("sono il figlio il mio pid è %d il pid di mio padre è %d\n",getpid(),getppid());
        break;
        default://codice padre
        wait(&status);
        //in assenza della wait() la stampa delle due stringhe del padre e del figlio è indeterministica
        printf("sono il padre il mio pid è %d il pid di mio padre è %d\n",getpid(),getppid());
        break;
    }
    return 0;
}
