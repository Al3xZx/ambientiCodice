#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define N 18
int main(int argc, char const *argv[]) {
    int tmp,k,l;
    int v[N]= {18,22,30,24,15,-6,7,18,9,30,20,-18,18,-12,-24,1,-60,3};
    int fd=open("Numeri.dat",O_CREAT|O_RDWR,0666);
    if(fd<0){
        printf("errore file\n");
        exit(-1);
    }
    write(fd,v,N*sizeof(int));
    printf("ho scritto sul file:\n");
    l=lseek(fd,0,SEEK_END)/sizeof(int);
    //l/=sizeof(int);
    printf("l=%d\n", l);
    lseek(fd,0,SEEK_SET);
    k=0;
    while(k<l){
        read(fd,&tmp,sizeof(int));
        printf("%d\n", tmp);
        k++;
    }
    close(fd);
    return 0;
}
