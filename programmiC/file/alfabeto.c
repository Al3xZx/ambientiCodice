#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
void stampaVettore(char* v, int n){
    int i;
    printf("[ ");
    for (i = 0; i < n; i++) {
        if (i < n-1) {
            printf("%c, ", v[i]);
        } else {
            printf("%c ]\n", v[i]);
        }
    }
}
int main(int argc, char const *argv[]) {
    int fd, i,n;
    char buffer[]="abcdefghilmnopqrstuvz";
    char bufferRead[21];
    fd = open("alfabeto.txt", O_CREAT|O_RDWR,0666);
    if(fd<0){
        printf("%s\n", "errore file");
        exit(-1);
    }
    write(fd,buffer,21*sizeof(char));
    /*
    close(fd);
    fd = open("alfabeto.txt", O_CREAT|O_RDWR,0666);<-------|
                                                           |                    */
    lseek(fd,0,SEEK_SET);//invece di chiudere e riaprire il file riporto la
                         //testina all'inizio del file e leggo 21 caratteri
    read(fd,bufferRead,21*sizeof(char));

    printf("%s\n",bufferRead);
    n=lseek(fd,0,SEEK_END);
    //stampaVettore(bufferRead,21);

    printf("%d\n",n );
    close(fd);
    return 0;
}
