#include <stdio.h>
int* incrementa(int* v, int l);
void vectorPrint(int* v, int l);
int* incrementa(int* v, int l){
    int vret[l];
    int* p = vret;
    for (size_t i = 0; i < l; i++) {
        vret[i]=v[i]+1;
    }
    return p;
}

void vectorPrint(int* v, int l){
    int i=0;
    printf("[");
    for (i = 0; i < l; i++) {
        if(i != l-1)
            printf(" %d,", *(v+i));
        else
            printf(" %d ]", *(v+i));
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int v[5]={1,2,3,4,5};
    int* pv = v;
    vectorPrint(pv, 5);
    pv = incrementa(v, 5);
    vectorPrint(pv, 5);
    return 0;
}
