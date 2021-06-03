#include "VetorEsparso.h"
typedef struct {
    int numlinhas;
    int numcolunas;
    VetorEsparso** v;
    
} MatrizEsparsa;


//Esta função deve alocar uma nova estrutura MatrizEsparsa e inicializá-la adequadamente. O parâmetro n
//indica o número de linhas da matriz, e m indica o número de colunas.
MatrizEsparsa* ME_Criar(int n, int m);

//Esta função deve retornar o número de linhas da matriz M.
int ME_NLinhas(MatrizEsparsa* M);
//Esta função deve retornar o número de colunas da matriz M.

int ME_MColunas(MatrizEsparsa* M);
/*
Esta função atribui valor na linha lin, coluna col da matriz esparsa M.Na prática, o VetorEsparso correspondenta a linha lin deve ser obtido por acesso direto ao arranjo das linhas. Depois, basta invocar a função
VE_Atribuir para atualizar o vetor esparso adequadamente.
Lembre-se que lin deve ser um valor entre 0 e n − 1 e que col deve ser um valor entre 0 e m − 1. Caso
qualquer um desses parametros estejam fora do intervalo, termine o programa com uma mensagem de erro
informando do acesso ilegal na posição informada.
*/
void ME_Atribuir(MatrizEsparsa* M, int lin, int col, double valor);

/*
Esta função retorna o valor armazenado na linha lin, coluna col da matriz esparsa M. Na prática, o
VetorEsparso correspondenta a linha lin deve ser obtido por acesso direto ao arranjo das linhas. Depois,
basta invocar a função VE_Buscar para pesquisar o valor da coluna col. Um exemplo (incompleto) da
implementação dessa função está descrita no início deste texto.
Lembre-se que lin deve ser um valor entre 0 e n − 1 e que col deve ser um valor entre 0 e m − 1. Caso
qualquer um desses parametros estejam fora do intervalo, termine o programa com uma mensagem de erro
informando do acesso ilegal na posição informada
*/
double ME_Buscar(MatrizEsparsa* M, int lin, int col);

/*
Esta função retorna o vetor esparso correspondente a linha lin da matriz M.
Lembre-se que lin deve ser um valor entre 0 e n − 1. Caso esteja fora deste intervalo, termine o programa
com uma mensagem de erro informando do acesso ilegal na posição informada.
ME_MultiplicaEscalar
*/

VetorEsparso* ME_ObterLinha(MatrizEsparsa* M, int lin);
/*
Esta função multiplica cada elemento diferente de zero da matriz esparsa M ao escalar alpha e armazena o
resultado de volta em M.
ME_MultiplicaVetor
*/
void ME_MultiplicaEscalar(MatrizEsparsa* M, double alpha);
/*Esta função calcula a multiplicação da matriz M pelo vetor v. O resultado desta operação é um novo vetor,
cuja i-ésima posição é o produto escalar entre a i-ésima linha de M e o vetor v.
Esta operação só é permitida se o número de colunas de M for o mesmo que a dimensão de v. Caso não seja,
termine o programa com uma mensagem de erro informando o número de colunas de M e a dimensão de v e
que devem ser iguais para que a operação seja possível.
*/
VetorEsparso* ME_MultiplicaVetor(MatrizEsparsa* M, VetorEsparso* v);
/*
Esta função retorna uma nova matriz tal que o valor de cada posição é a soma dos elementos correspondentes
das matrizes esparsas M e A. Implemente esta função para que seja eficiente, de forma que acesse o mínimo
possível de posições zeradas em ambas as matrizes de entrada.
Esta operação só é permitida se o número de linhas e colunas das matrizes M e A for o mesmo. Caso não seja,
termine o programa com uma mensagem de erro informando o número de linhas e colunas das matrizes e que
devem ser iguais para que a operação seja possível.*/
MatrizEsparsa* ME_SomaMatriz(MatrizEsparsa* M, MatrizEsparsa* A);

/*
Esta função carrega uma matriz de um arquivo salvo em nome_do_arquivo em uma MatrizEsparsa. O
arquivo tem o seguinte formato:
n
m
nnz
linha;coluna;valor
linha;coluna;valor
....
linha;coluna;valor
*/
MatrizEsparsa* ME_Carregar(char* nome_do_arquivo);

//Esta função salva a matriz esparsa M no arquivo nome_do_arquivo no formato descrito na função ME_Carregar.
void ME_Salvar(MatrizEsparsa* M, char* nome_do_arquivo);
//Esta função libera todos os recursos alocados dinamicamente para a matriz esparsa M.
void ME_Destruir(MatrizEsparsa* M);
void imprimir(MatrizEsparsa* m);