#include<stdio.h>
#include<stdlib.h>
/*#include<stdbool.h>*/

typedef enum{false,true} bool;

int** create(int, int);
void read(int**, int, int);
void print(int**, int, int);
void restituisci_max_min_vett(int**,int, int ,int* ,int* ,int* ,int*);

int** create(int r, int c){
 int** mat=(int**) malloc (r*sizeof(int*));
 if(mat==NULL){
  printf("Memoria non disponibile \n");
  exit(-1);
 }
 else{
  int i;
  for(i=0;i<r;i++){
   mat[i]=(int*) malloc (c*sizeof(int));
   if(mat[i]==NULL){
    printf("Memoria non disponibile");
    free(mat);
    exit(-1);
   }
  }
 }
 return mat;
}

void read(int** mat, int r, int c){
 int i,j;
 for(i=0; i<r; i++){
  for(j=0; j<c; j++){
   printf("Inserisci elemento [%d,%d] >",i,j);
   scanf("%d", &mat[i][j]);
  }
 }
}


void print(int** mat, int r, int c){
 int i,j;
 for(i=0; i<r; i++){
  for(j=0; j<c; j++){
   printf("%d ", mat[i][j]);
  }
  printf("\n");
 }
}

void restituisci_max_min_vett(int** mat, int r, int c,int* v,int* dimv, int* max, int* min){
int i,j,k,dim;
int vmax=mat[0][0];
int vmin=mat[0][0];
/*printf("%d",vmax);*/
for (i=0; i<r;i++) {
 for (j=0; j<c;j++) {
  if(mat[i][j]>vmax) vmax=mat[i][j];
  if(i==j && mat[i][j]<vmin) vmin=mat[i][j];
 }
}
*max=vmax;
*min=vmin;
dim=0;

for (i=1; i<r;i+=2) {
 for (j=0; j<c;j++) {
  if(mat[i][j]>2*vmin) {
      dim++;
     // printf("mat[%d][%d] = %d\n",i,j,mat[i][j] );
  }
 }
}
*dimv=dim;
if(dim>0){
    printf("indirizzo v = %p\n",v);
    v=(int*) malloc(dim*sizeof(int));
    printf("indirizzo v = %p\n",v);
    k=0;
    for (i=1; i<r;i+=2) {
        for (j=0; j<c;j++) {
            //printf("vmin %d\n", vmin);
            if(mat[i][j]>2*vmin){
                //printf("mat[%d][%d] = %d\n",i,j,mat[i][j] );
                v[k]=mat[i][j];
                //printf("v[%d] = %d\n",k,v[k]);
                k++;
            }
        }
    }
}
    /*debug print*/
    printf("Vettore = ");
    for(i=0;i<dim;i++){
        printf("%d ",v[i]);
    }
}


int main(){
 int** mat;
 int i,r,c,k;
 int* v;
 int dimv;
 int max;
 int min;
 printf("Inserisci numero righe: ");
 scanf("%d",&r);
 printf("Inserisci numero colonne: ");
 scanf("%d",&c);
 mat=create(r,c);
 printf("Inserisci elementi: ");
 read(mat,r,c);
 printf("Matrice letta: \n");
 print(mat,r,c);
 printf("\n");

printf("indirizzo v = %p\n",v);
printf("inizia restituisci_max_min_vett\n");
 restituisci_max_min_vett(mat,r,c,v,&dimv,&max,&min);
printf("finisce restituisci_max_min_vett\n");
printf("indirizzo v = %p\n",v);

 printf("max: %d \n", max);
printf("min: %d \n", min);
printf("Vettore = ");
for(i=0;i<dimv;i++){
   printf("%d ",v[i]);
}
 printf ("\n");
 printf ("Libero la memoria... \n");
 for (i=0;i<r;i++){
  free(mat[i]);
 }
 free(mat);
 /*free(v);*/
 return 0;
}
