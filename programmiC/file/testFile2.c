#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void stampaVettore(int* v, int n){
    int i;
    printf("[ ");
    for (i = 0; i < n; i++) {
        if (i < n-1) {
            printf("%d, ", v[i]);
        } else {
            printf("%d ]\n", v[i]);
        }
    }
}
int main(int argc, char const *argv[]) {
    int fd;
    int n;
    int* buffer;
    fd=open("numeriTest.bin",O_RDONLY,0644);
    if (fd<0) {
        printf("%s\n", "errore file");
        exit(-1);
    }
    n=((lseek(fd,0,SEEK_END)-1)-lseek(fd,0,SEEK_SET))/sizeof(int);
    printf("il file contiene %d elementi\n", n);
    buffer=(int*)malloc(n*sizeof(int));
    if (buffer==NULL) {
        printf("%s\n", "spaziio non disponibile");
        exit(-1);
    }
    read(fd,buffer,n*sizeof(int));
    printf("gli elementi sono:\n");
    stampaVettore(buffer,n);
    /*read(fd,buffer,n*sizeof(int));
    stampaVettore(buffer,n);*/
    return 0;
}
