#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int* p;
    p=(int*) malloc(sizeof(int));
    p=NULL;
    if(p==NULL){
        printf("%s\n","memoria non disponibile");
        return 1;
    }
    *p=100;
    printf("p = %p, *p = %d\n",p,*p);
    free(p);
    printf("p = %p, *p = %d\n",p,*p);
    return 0;
}
