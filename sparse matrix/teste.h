#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrizEsparsa.h"
#include "VetorEsparso.h"
#define  BUF_SIZE 1048576

double** MD_Carregar(char* nome_do_arquivo, int* n, int* m){
double** matriz;
int *x;
int i , j;
double v;
int linha, coluna;
double valor;
char* buf = malloc(sizeof(char) * BUF_SIZE);

FILE* fp = fopen(nome_do_arquivo,"r");

fgets(buf,BUF_SIZE,fp);
sscanf(buf, "%d\n", &n);
fgets(buf,BUF_SIZE,fp);
sscanf(buf, "%d\n", &m);


for(i = 0 ; i <n; i++){
    for(j = 0; j <m;j++){
    fgets(buf,BUF_SIZE,fp);
    sscanf(buf,"%d;%d",&linha,&coluna);

    printf("%d  ",linha);
    printf("%d ",coluna);
    }
  
}
free(buf);
return matriz;


}

void MD_MultiplicarMatrizVetor(double** M, int n, int m, double *v, double *resultado){


    int i , j ;
            for (i = 0; i < n; i++) {
            resultado[i] = 0;
                for (j = 0; j < m; j++)
                resultado[i] = resultado[i] + M[i][j] * v[j];




}





