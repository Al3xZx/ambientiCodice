
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N 8
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
void generaVettore(int* v, int n){
    int i;
    for (i = 0; i < n; i++)
        v[i]=rand()%100;
}
int main(int argc, char const *argv[]) {
    int fd;
    int vet[N];
    int buffer[N];
    generaVettore(vet,N);
    printf("il vettore che scriverò su file è:\n");
    stampaVettore(vet,N);
    fd=open("numeriTest.bin",O_CREAT|O_RDWR|O_APPEND,0644);
    if (fd<0) {
        printf("%s\n", "errore file");
        exit(-1);
    }
    write(fd,vet,N*sizeof(int));
    lseek(fd,0,SEEK_SET);
    read(fd,buffer,N*sizeof(int));
    printf("il vettore su file è:\n");
    stampaVettore(buffer,N);
    return 0;
}
