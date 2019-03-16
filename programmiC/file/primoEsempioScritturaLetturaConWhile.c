#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define DIM 97

void printVect(int*, int);

int main(int argc, char const *argv[]) {
    int v[DIM];
    int bufferRead[DIM/DIM];
    int fd1, fd2, i;

    for (i = 0; i < DIM; i++)
        v[i]=rand()%100;
    printf("il vettore è:\n");
    printVect(v,DIM);

    fd1=open("numFile",O_TRUNC|O_CREAT|O_WRONLY,0644);
    if(fd1<0)
        printf("errore file!\n");
    printf("scrivo sul file con file descriptor %d\n",fd1);
    write(fd1,v,DIM*sizeof(int));
    close(fd1);

    fd2=open("numFile",O_RDONLY,0644);
    if(fd2<0)
        printf("errore file!\n");
    printf("leggo dal file con file descriptor %d\n",fd2);
    while(read(fd2,bufferRead,(DIM/DIM)*sizeof(int))>0){/*in questo modo leggo il file a blocchi*/
        printVect(bufferRead,DIM/DIM);
    }
    close(fd2);



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
