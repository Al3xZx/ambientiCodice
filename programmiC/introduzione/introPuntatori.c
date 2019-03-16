#include <stdio.h>
int main(int argc, char const *argv[]) {
    /*variaili*/
    int a = 5, b=10, i=0;
    int v[7] = {4,6,8,0,3,2,5};
    int* pi = &a;
    printf("a= %d, b= %d \n",a,b);
    b = *pi; /*eqivalente a b=a;*/
    printf("a= %d, b= %d \n",a,b);
    *pi=30;
    printf("a= %d, b= %d \n",a,b);
    /*vettori*/
    /*int* pv = &v[0];*/
    /*eqivalente a*/ int* pv = v;
    for (i = 0; i < 7; i++) {
        printf("v[%d]= %d\n",i,*(pv+i));
    }
    printf("\n");
    for (i = 0; i < 7; i++) {
        *(pv+i)=i;
    }
    for (i = 0; i < 7; i++) {
        printf("v[%d]= %d\n",i,*(v+i));
        /* *(v+i) è eqivalente A *(pv+i) infatti v e pv sono entrambi puntatori*/
    }
    return 0;
}
