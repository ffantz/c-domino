#ifndef ___LISTA_SIMPLESMENTE_ENCADEADA___
#define ___LISTA_SIMPLESMENTE_ENCADEADA___

#include "Domino.h"

/* TAD Utilizado para guardar as pecas da mesa e da mão dos jogadores */

/* --------
    A ordenação na mão do jogador é a seguinte:

    - A ordenação é decrescente
    - Prioridade: o lado direito ser maior conta mais do que o esquerdo
    - A ordem relativa a todas as peças é printada na função embaralhapecas

*/

/* ------
    Não existe ordenação nas pecas da mesa.
    Para ela, só é utilizado as funções insere inicio e insere final
*/

typedef struct NoSimples {
    tPeca V;
    struct NoSimples* prox;
} tNoSimples;

typedef struct {
    tNoSimples* inicio;
    tNoSimples* final;
    int numElem;
} tListaSimplesEncadeada;

typedef struct {
    tListaSimplesEncadeada lista;
    char *nome;
    int jogador;
} tJogador;

// ***********************************************
/*Inicializa a lista */
void initListaSimples(tListaSimplesEncadeada* L);

// ***********************************************
/*Limpa toda a lista, liberanto todo o espaço da memória */
void limpaListaSimples(tListaSimplesEncadeada* L);

// ***********************************************
/* Imprime a lista na ordem Inicio -> final */
void imprimeListaSimples(tListaSimplesEncadeada L);

// ***********************************************
/* Insere um elemento na ultima posição da lista
   Ou melhor, na ponta direita da mesa */
bool insereFinalListaSimples(tListaSimplesEncadeada* L, tPeca peca);

// ***********************************************
/* Insere um elemento na primeira posição da lista
   Ou melhor, na ponta esquerda da mesa */
bool insereInicioListaSimples(tListaSimplesEncadeada* L, tPeca peca);

// ***********************************************
/* Aloca um nó. Utilizado nas funções de inserir */
tNoSimples* alocaNoSimples(tPeca peca);

// ***********************************************
/* Retorna o tamanho da lista */
int tamListaSimples(tListaSimplesEncadeada L);

// ***********************************************
/* Busca a peca de valor especificado
   Usada para remover elemento da lista */
tNoSimples* buscaElementoListaSimples(tListaSimplesEncadeada L,
  tNoSimples** anterior, int pontas[], bool** esquerda, bool** inicio);

// ***********************************************
/*Insere de forma em que a soma dos valores da peca na ordem DECRESCENTE
  Necessário para agilizar a busca da melhor peca*/
bool insereOrdenadoListaSimples(tListaSimplesEncadeada* L, tPeca peca);

// ***********************************************
/*Remove a peca de valor especificado
  Usada para fazer um jogador colocar uma peca na mesa*/
bool removeElementoListaSimples(tListaSimplesEncadeada* L,
  int pontas[], bool* esquerda, bool* inicio, tPeca* peca);

// ***********************************************
/*Remove a peca de um endereço especificado
  Usada para o embaralhamento das pecas*/
tPeca removeElementoPosListaSimples(tListaSimplesEncadeada* L, int index);

// ***********************************************
/*Soma de todos os valores dos elementos da lista
  Usada para contar a quantidade de pontos de cada jogador*/
int somaListaSimples(tListaSimplesEncadeada L);

#endif // ___LISTA_SIMPLESMENTE_ENCADEADA___