#ifndef ___PILHA___
#define ___PILHA___

#include "Domino.h"

/*
    A pilha é usada para guardas as pedras do APE
    APE = Agrupamento de pedras embaralhado
*/

typedef struct Pilha {
    tPeca* V;
    int topo;
} tPilha;

// ***********************************************
/*Inicializa as variáveis da pilha*/
bool initPilha(tPilha* P);

// ***********************************************
/*Limpa toda a pilha. Para usar a pilha novamente é
necessário uma nova inicialização*/
void limpaPilha(tPilha* P);

// ***********************************************
/*Insere um novo elemento na pilha*/
bool empilha(tPilha** P, tPeca pedra);

// ***********************************************
/*Retira um elemento da pilha*/
bool desempilha(tPilha* P, tPeca* pedra);

// ***********************************************
/*Imprime a próxima pedra a ser retirada*/
void mostraTopoPilha(tPilha P);

#endif // ___PILHA___