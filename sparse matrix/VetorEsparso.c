#include <stdio.h>
#include <stdlib.h>
#include "VetorEsparso.h"

void THEA_Redimensionar(VetorEsparso * v, int m_novo) {
    ELEM * nova, * antiga; // ponteiro para a nova tabela e uma para a tabela velha
    int i, m_antigo;

    nova = malloc(sizeof(ELEM) * m_novo);
    for (i = 0; i < m_novo; i++) {
        nova[i].estado = E_LIVRE;
    }
    antiga = v -> th;
    m_antigo = v -> m;
    v -> th = nova;
    v -> m = m_novo;
    v -> n = 0;

    for (i = 0; i < m_antigo; i++) {
        if (antiga[i].estado == E_OCUPADO) {
            THEA_Inserir(v, antiga[i].chave, antiga[i].valor);
        }
    }

    free(antiga);
}

lista * ILISTA_Criar() {
    lista * novo;

    novo = (lista * ) malloc(sizeof(lista));
    novo -> inicio = NULL;
    novo -> fim = NULL;
    novo -> tam = 0;

    return novo;
}

void ILIST_INSERIR(lista * l, int dado) {
    No * novo;

    novo = malloc(sizeof(No));
    novo -> dado = dado;
    novo -> proximo = NULL;

    if ((ILISTA_Vazia(l))) {
        l -> inicio = novo;
        l -> fim = novo;

    } else {
        l -> fim -> proximo = novo;
        l -> fim = novo;
    }

    l -> tam++;
}

int ILISTA_Tamanho(lista * l) {
    return l -> tam;
}
int ILISTA_Vazia(lista * l) {
    return l -> tam == 0 ? 1 : 0;

}

// remover um elemento da lista
int ILISTA_Remover(lista * li, int dado) {

    if (li == NULL)
        return 0;
    if ((ILISTA_Vazia(li)))
        return 0;
    No * ant, * no = li -> inicio;
    ant = NULL;
    while (no != NULL) {
        if (no -> dado == dado) {
            if (ant == NULL) {
                if (li -> tam == 1) {
                    li -> fim = NULL;
                }
                li -> inicio = no -> proximo;
            } else {
                if (no -> proximo == NULL) {
                    li -> fim = ant;
                }
                ant -> proximo = no -> proximo;

            }
            free(no);
            li -> tam--;
            return 1;
        }
        ant = no;
        no = no -> proximo;

    }

    return 0;

}
// imprimir a lista
void ILISTA_Imprimir(lista * lista) {

    No * n;
    for (n = lista -> inicio; n != NULL; n = n -> proximo) {
        printf("%d \n", n -> dado);
    }
    printf("\n");
}

int THEA_Hash(VetorEsparso * v, int chave, int k) {

    return ((chave % v -> m) + k) % v -> m;
}

int THEA_Inserir(VetorEsparso * v, int chave, double valor) {

    int h, k, h_inicial;
    k = 0;

    if (v -> n > v -> m / 2) {
        printf("redimensionada de %d para %d \n", v -> m, v -> m * 2);
        THEA_Redimensionar(v, v -> m * 2);
    }

    h = THEA_Hash(v, chave, k);
    h_inicial = h;

    while (v -> th[h].estado == E_OCUPADO) {
        if (v -> th[h].chave == chave) {
            v -> n--;
            break;
        }
        k++;
        h = THEA_Hash(v, chave, k);

        if (h == h_inicial)
            return -1;
    }

    v -> n ++;
    v -> th[h].chave = chave;
    v -> th[h].valor = valor;
    v -> th[h].estado = E_OCUPADO;

    return h;
}
int THEA_Buscar(VetorEsparso * v, int chave) {
    int h, h_inicial, k;
    k = 0;

    h = THEA_Hash(v, chave, k);
    h_inicial = h;

    while (v -> th[h].estado != E_LIVRE) {
        if (v -> th[h].estado == E_OCUPADO && v -> th[h].chave == chave) {
            return h;
        }
        k++;
        h = THEA_Hash(v, chave, k);

        if (h_inicial == h) {
            return -1;
        }
    }
    return -1;
}

int THEA_Remover(VetorEsparso * v, int chave) {

    int pos;

    pos = THEA_Buscar(v, chave);
    if (pos == -1) return -1;

    v -> th[pos].estado = E_APAGADO;
    v -> n--;
    return pos;
}

void THEA_Imprimir(VetorEsparso * v) {

    int i;
    char estado;

    for (i = 0; i < v -> m; i++) {
        if (v -> th[i].estado == E_OCUPADO)
            estado = 'O';

        else if (v -> th[i].estado == E_APAGADO)
            estado = 'A';

        else
            estado = 'L';

        printf("%d: %d, %.1f, %c \n", i, v -> th[i].chave, v -> th[i].valor, estado);
    }
    printf("\n");
}

VetorEsparso * VE_Criar(int m) {

    VetorEsparso * novo;
    int i;

    novo = malloc(sizeof(VetorEsparso));
    novo ->n = 0;
    novo -> th = malloc(sizeof(ELEM) * 5);
    novo -> qtde_colunas = m;
    novo -> m = 5;

    novo -> li = ILISTA_Criar();

    for (i = 0; i < novo->m; i++) {
        novo -> th[i].estado = E_LIVRE;

    }
    

    return novo;
}

int VE_Dimensao(VetorEsparso * V) {
    return (V -> qtde_colunas);
}

int VE_NNaoZero(VetorEsparso * v) {

    return (v -> n);
}

/*você deve verificar se a chave col já está inserida na estrutura subjacente. Caso não esteja, o elemento deve ser inserido na estrutura
com o valor. Caso já esteja, o valor deve ser atualizado na estrutura. Caso o valor atribuído seja zero, a
chave deve ser removida da estrutura, uma vez que a idéia é que os elementos zero não sejam armazenados.
Lembre-se que col deve ser um valor entre 0 e m − 1. Caso esteja fora deste intervalo, termine o programa
com uma mensagem de erro informando do acesso ilegal na posição informada*/

void VE_Atribuir(VetorEsparso * v, int col, double valor) {

    lista * l;
    if (col < 0 || col > v -> qtde_colunas) {
        printf("col está fora do intervalo [0 %d)\n", (v -> qtde_colunas));
        exit(1);

    }
    
    int aux = THEA_Buscar(v, col);

    if (valor == 0) {
        if (aux != -1) {
            THEA_Remover(v, col);
            ILISTA_Remover(v -> li, col);
        }
    }
    if (aux != -1 && valor != 0) {
        v -> th[aux].valor = valor;

    }
    if (aux == -1 && valor != 0) {
        THEA_Inserir(v, col, valor);
        ILIST_INSERIR(v -> li, col);
    
    }

}

/*Esta função retorna o valor armazenado no vetor esparso v na coluna col. Lembre-se que os valores 0 não
precisam ser armazenados no vetor. Portanto, caso a chave col não esteja na estrutura, basta retornar 0.
Lembre-se que col deve ser um valor entre 0 e m − 1. Caso esteja fora deste intervalo, termine o programa
com uma mensagem de erro informando do acesso ilegal na posição informada.
*/
double VE_Buscar(VetorEsparso * v, int col) {

    if (col < 0 || col > v -> qtde_colunas) {
        printf("col está fora do intervalo [0  %d)\n", (v -> qtde_colunas));
        exit(1);
    }
    
    int aux = THEA_Buscar(v, col);
    if (aux != -1) {
        return v -> th[aux].valor;
    } else if (aux == -1) {
        return 0; // if (aux == -1) return 0;
    }
}

/*Esta função calcula o produto escalar entre os vetores v e u. Verifique a definição de algébrica de produto
escalar na wikipédia.
Esta operação só é permitida se o número de colunas dos vetores v e u for o mesmo. Caso não seja, termine o
programa com uma mensagem de erro informando o número de colunas dos vetores e que devem ser iguais
para que a operação seja possível.
Implemente esta operação de forma eficiente, iterando sobre o vetor com o menor número de entradas
diferentes de zero. DICA: Você pode ter que inserir uma operação no TAD da estrutura de armazenamento
dos dados (tabela hash, árvore), que retorne as chaves dos elementos na estrutura e outra operação que
retorne o número de chaves armazenadas. */

double PE(VetorEsparso * v1, VetorEsparso * v2) {
    double soma = 0, i = 0;
    lista * li;

    for (i = 0; i < li -> tam; i++) {
        soma += VE_Buscar(v1, i) * VE_Buscar(v2, i);
    }

    return soma;
}

double VE_ProdutoEscalar(VetorEsparso * v, VetorEsparso * u) {

    int dim_v = VE_Dimensao(v);
    int dim_u = VE_Dimensao(u);

    if (dim_v != dim_u) {
        printf("%d %d o número de colunas de ambos os vetores devem ser iguais\n", dim_u, dim_v);
        return 0;
    }
    if (VE_NNaoZero(v) <= VE_NNaoZero(u)) {
        double x = PE(v, u);
        return x;
    } else {
        double y = PE(u, v);
        return y;
    }
}

void VE_MultiplicaEscalar(VetorEsparso * v, double alpha) {
    float total = 0;
    int i;
    lista * l;

    for (i = 0; i < l -> tam; i++) {
        total = VE_Buscar(v, i);
        total = total * alpha;
        VE_Atribuir(v, i, total);
    }

}

VetorEsparso * VE_MultiplicaVetor(VetorEsparso * v, VetorEsparso * u) {
    int dim_v = VE_Dimensao(v);
    int dim_u = VE_Dimensao(u);
    double resultado;
    lista * l;

    if (dim_v != dim_u) {
        printf("%d %d o número de colunas de ambos os vetores devem ser iguais\n", dim_u, dim_v);
        return NULL;
    }
    if (v -> li -> tam < u -> li -> tam) {
        l = v -> li;
    } else {
        l = u -> li;
    }

    VetorEsparso * aux = VE_Criar(dim_u);

    No * n = l -> inicio;

    for (int i = 0; i < l -> tam; i++) {
        resultado = VE_Buscar(u, n -> dado) * VE_Buscar(v, n -> dado);
        VE_Atribuir(aux, n -> dado, resultado);
        n = n -> proximo;
    }

    return aux;

}

VetorEsparso * VE_SomaVetor(VetorEsparso * v, VetorEsparso * u) {
    int dim_v = VE_Dimensao(v);
    int dim_u = VE_Dimensao(u);
    double resultado;
    lista * l;

    if (dim_v != dim_u) {
        printf("%d %d o número de colunas de ambos os vetores devem ser iguais\n", dim_u, dim_v);
        return NULL;
    }
    if (v -> li -> tam < u -> li -> tam) {
        l = v -> li;
    } else {
        l = u -> li;
    }

    VetorEsparso * aux = VE_Criar(dim_u);

    No * n = l -> inicio;

    for (int i = 0; i < l -> tam; i++) {
        resultado = VE_Buscar(u, n -> dado) + VE_Buscar(v, n -> dado);
        VE_Atribuir(aux, n -> dado, resultado);
        n = n -> proximo;
    }

    return aux;

}

void libera_lista(lista * li) {

    if (li != NULL) {
        No * no = li -> inicio, * aux = NULL;
        while (no != NULL) {
            aux = no;
            no = no -> proximo;
            free(aux);
        }
        free(li);
    }

}

void VE_Destruir(VetorEsparso * v) {
    libera_lista(v -> li);
    free(v -> th);
    free(v);
}