#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrizEsparsa.h"
#include "VetorEsparso.h"
#define BUF_SIZE 1048576

MatrizEsparsa * ME_Criar(int n, int m) {

    MatrizEsparsa * a = (MatrizEsparsa * ) malloc(sizeof(MatrizEsparsa));
    a -> numcolunas = m;
    a -> numlinhas = n;
    a -> v = (VetorEsparso ** ) malloc(sizeof(VetorEsparso * ) * n);

    for (int i = 0; i < a -> numlinhas; i++) {
        a -> v[i] = VE_Criar(a -> numcolunas);
    }

    return a;

}

int ME_NLinhas(MatrizEsparsa * M) {

    return M -> numlinhas;

}
int ME_NColunas(MatrizEsparsa * M) {

    return M -> numcolunas;

}
VetorEsparso * ME_ObterLinha(MatrizEsparsa * M, int lin) {

    if (lin < 0 || lin > M -> numlinhas) {
        printf("lin deve estar no intervalo [0,%d), mas lin = %d", (M -> numlinhas), lin);
        exit(1);
    } else

        return M -> v[lin];

}

void ME_Atribuir(MatrizEsparsa * M, int lin, int col, double valor) {

    VetorEsparso * v;
    v = ME_ObterLinha(M, lin);
    VE_Atribuir(v, col, valor);

}
double ME_Buscar(MatrizEsparsa * M, int lin, int col) {
    VetorEsparso * v;
    v = ME_ObterLinha(M, lin);
    return VE_Buscar(v, col);

}
VetorEsparso * ME_MultiplicaVetor(MatrizEsparsa * M, VetorEsparso * v) {
    float pe = 0;
    int i;
    VetorEsparso * x = VE_Criar(M -> numlinhas);

    if (M -> numcolunas != VE_Dimensao(v)) {
        printf("o numero de colunas da matriz M deve ser o mesmo que a dimensão de v, col = %d dim = %d", M -> numcolunas, v -> m);
        exit(1);
    } else {
        for (i = 0; i < M -> numlinhas; i++) {
            pe = VE_ProdutoEscalar(ME_ObterLinha(M, i), v);
            VE_Atribuir(x, i, pe);

        }

    }
    return x;

}
MatrizEsparsa * ME_SomaMatriz(MatrizEsparsa * M, MatrizEsparsa * A) {
    if (M -> numcolunas != A -> numcolunas || M -> numlinhas != A -> numlinhas) {
        printf("numero de linhas e colunas das duas matrizes devem ser iguais");
        exit(1);
    }
    int i;
    double total = 0, total2 = 0;
    MatrizEsparsa * x = ME_Criar(M -> numlinhas, M -> numcolunas);

    for (i = 0; i < M -> numlinhas; i++) {
        for (int j = 0; j < A -> numcolunas; j++) {
            total = ME_Buscar(A, i, j);
            total2 = ME_Buscar(M, i, j);
            double resultado = total + total2;
            ME_Atribuir(x, i, j, resultado);
        }

    }

    return x;
}

void ME_MultiplicaEscalar(MatrizEsparsa * M, double alpha) {

    float total = 0;
    int i;
    VetorEsparso * v;

    for (int i = 0; i < M -> numlinhas; i++) {
        for (int j = 0; j < M -> numcolunas; j++) {
            total = ME_Buscar(M, i, j);
            total *= alpha;
            ME_Atribuir(M, i, j, total);
        }

    }

}

void imprimir(MatrizEsparsa * m) {
    int i, j;

    for (i = 0; i < m -> numlinhas; i++) {

        THEA_Imprimir(m -> v[i]);
    }

    printf("\n");
}

MatrizEsparsa * ME_Carregar(char * nome_do_arquivo) {

    int i, m, n, nmz, * x;
    double v;
    int linha, coluna;
    double valor;
    char * buf = malloc(sizeof(char) * BUF_SIZE);

    FILE * fp = fopen(nome_do_arquivo, "r");

    fgets(buf, BUF_SIZE, fp);
    sscanf(buf, "%d\n", & n);
    fgets(buf, BUF_SIZE, fp);
    sscanf(buf, "%d\n", & m);
    fgets(buf, BUF_SIZE, fp);
    sscanf(buf, "%d", & nmz);

    MatrizEsparsa * matriz = ME_Criar(n, m);

    for (i = 0; i < nmz; i++) {
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf, "%d;%d;%lf", & linha, & coluna, & valor);

        printf("%d  ", linha);
        printf("%d ", coluna);
        printf("%lf\n", valor);
        ME_Atribuir(matriz, linha, coluna, valor);

    }
    free(buf);
    return matriz;

}
void ME_Destruir(MatrizEsparsa * M) {

    for (int i = 0; i < M -> numlinhas; i++) {
        VE_Destruir(M -> v[i]);
    }
    free(M -> v);
    free(M);

}

void ME_Salvar(MatrizEsparsa * M, char * nome_do_arquivo) {

    char buffer[70];
    int i, j;
    int n, m, nnz;
    double val;

    FILE * fp = fopen(nome_do_arquivo, "w");
    VetorEsparso * v;
    v = VE_Criar(M -> numcolunas);
    n = M -> numlinhas;
    m = M -> numcolunas;
    nnz = VE_NNaoZero(v);

    sprintf(buffer, "%d\n%d\n%d\n", n, m, nnz);
    fputs(buffer, fp);

    for (i = 0; i < M -> numlinhas; i++) {
        for (j = 0; j < M -> numcolunas; j++) {
            val = ME_Buscar(M, i, j);
            sprintf(buffer, "%d;%d;%.3lf\n", i, j, val);
            fputs(buffer, fp);

        }
    }

    fclose(fp);

}