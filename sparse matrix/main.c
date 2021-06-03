#include <stdio.h>
#include <stdlib.h>
#include "VetorEsparso.h"
#include "MatrizEsparsa.h"
#include <string.h>

void main(){

VetorEsparso* v = VE_Criar(1);
lista* l = ILISTA_Criar();
MatrizEsparsa* m = ME_Criar(1,1);

ME_Atribuir(m,0,0,1);
ME_Atribuir(m,0,1,3);
/*
ME_Atribuir(m,1,0,6);
ME_Atribuir(m,1,1,4);
ME_Atribuir(m,2,0,4);
ME_Atribuir(m,2,1,4);
*/
ME_Salvar(m,"teste.txt");

int t ;
printf("TTTT %d",l->tam);

imprimir(m);


/*
double **a;
int n = 0;
int m1 = 0;
a = MD_Carregar("matriz.txt", &n, &m1);
*/



}

