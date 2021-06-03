#pragma once

typedef enum ESTADO {
 E_LIVRE,
 E_OCUPADO,
 E_APAGADO
} ESTADO;

typedef struct ELEM {
    int chave; // coluna
    double valor;
    ESTADO estado;
}ELEM;

typedef struct No {
    int dado;
    struct No *proximo;
}No;
typedef struct {
    No *inicio, *fim;
    int tam;
}lista;

typedef struct VetorEsparso{
 int m; // tamanho total, é a linha
 ELEM* th;
 int n; // quantidade total de posições ocupadas
 int qtde_colunas;
 lista* li;
}VetorEsparso;



//Esta função deve alocar uma nova estrutura VetorEsparso e inicializá-la adequadamente. O parâmetro m indica o número de colunas do vetor. m também é chamado de dimensão do vetor.
VetorEsparso* VE_Criar(int m);
//Esta função retorna a dimensão do vetor v, ou seja, o número de colunas.
int VE_Dimensao(VetorEsparso* v);
//Esta função retorna o número de elementos diferentes de zero armazenados no vetor esparso v.
int VE_NNaoZero(VetorEsparso* V);
/*Esta função atribui valor na coluna col do vetor esparso v. Note que, na prática, você deve verificar se a
chave col já está inserida na estrutura subjacente. Caso não esteja, o elemento deve ser inserido na estrutura
com o valor. Caso já esteja, o valor deve ser atualizado na estrutura. Caso o valor atribuído seja zero, a
chave deve ser removida da estrutura, uma vez que a idéia é que os elementos zero não sejam armazenados.
Lembre-se que col deve ser um valor entre 0 e m − 1. Caso esteja fora deste intervalo, termine o programa
com uma mensagem de erro informando do acesso ilegal na posição informada*/
void VE_Atribuir(VetorEsparso* v, int col, double valor);
/*Esta função retorna o valor armazenado no vetor esparso v na coluna col. Lembre-se que os valores 0 não
precisam ser armazenados no vetor. Portanto, caso a chave col não esteja na estrutura, basta retornar 0.
Lembre-se que col deve ser um valor entre 0 e m − 1. Caso esteja fora deste intervalo, termine o programa
com uma mensagem de erro informando do acesso ilegal na posição informada.
*/
double VE_Buscar(VetorEsparso* v, int col);

/*Esta função calcula o produto escalar entre os vetores v e u. Verifique a definição de algébrica de produto
escalar na wikipédia.
Esta operação só é permitida se o número de colunas dos vetores v e u for o mesmo. Caso não seja, termine o
programa com uma mensagem de erro informando o número de colunas dos vetores e que devem ser iguais
para que a operação seja possível.
Implemente esta operação de forma eficiente, iterando sobre o vetor com o menor número de entradas
diferentes de zero. DICA: Você pode ter que inserir uma operação no TAD da estrutura de armazenamento
dos dados (tabela hash, árvore), que retorne as chaves dos elementos na estrutura e outra operação que
retorne o número de chaves armazenadas. */

double VE_ProdutoEscalar(VetorEsparso* v, VetorEsparso* u);

/*Esta função multiplica cada elemento diferente de zero do vetor esparso v ao escalar alpha e armazena o
resultado de volta no vetor. Implemente esta função para que seja eficiente, de forma que acesse o mínimo
possível de posições com valor zero no vetor v.*/
void VE_MultiplicaEscalar(VetorEsparso* v, double alpha);
/*

Esta função retorna um novo vetor tal que cada posição é o produto dos elementos correspondentes nos
vetores esparsos u e v. Implemente esta função para que seja eficiente, de forma que acesse o mínimo possível
de posições zeradas em ambos vetores de entrada.
Esta operação só é permitida se o número de colunas dos vetores v e u for o mesmo. Caso não seja, termine o
programa com uma mensagem de erro informando o número de colunas dos vetores e que devem ser iguais
para que a operação seja possível.
*/
VetorEsparso* VE_MultiplicaVetor(VetorEsparso* v, VetorEsparso* u);

/*

Esta função retorna um novo vetor tal que o valor de cada posição é a soma dos elementos correspondentes
nos vetores esparsos u e v. Implemente esta função para que seja eficiente, de forma que acesse o mínimo
possível de posições zeradas em ambos vetores de entrada.
Esta operação só é permitida se o número de colunas dos vetores v e u for o mesmo. Caso não seja, termine o
programa com uma mensagem de erro informando o número de colunas dos vetores e que devem ser iguais
para que a operação seja possível.
*/
VetorEsparso* VE_SomaVetor(VetorEsparso* v, VetorEsparso* u);

//Esta função libera todos os recursos alocados dinamicamente para o vetor esparso v.
void VE_Destruir(VetorEsparso* v);


//funções auxiliares
int THEA_Hash(VetorEsparso* v, int chave, int k);
int THEA_Inserir(VetorEsparso* v, int chave, double valor);
int THEA_Buscar (VetorEsparso* v, int chave);
int THEA_Remover(VetorEsparso* v,int chave);
void THEA_Imprimir(VetorEsparso* v);

lista* ILISTA_Criar();
int ILISTA_Tamanho(lista *l);
int ILISTA_Vazia(lista *l);
//lista_no* ILISTA_Buscar(lista_no *l, int dado);
int ILISTA_Remover(lista *l, int dado);
void ILISTA_Imprimir(lista *l);
lista* ILISTA_Buscar(lista* l, int dado);
void ILIST_INSERIR(lista *l, int dado);


 double PE(VetorEsparso * v1, VetorEsparso * v2);