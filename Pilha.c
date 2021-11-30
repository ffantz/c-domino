#include "Pilha.h"

// ***********************************************
// ******                                   ******
// ***********************************************
bool initPilha(tPilha* pilha) {
    pilha->topo = -1; // define o topo como -1 para inicializar
    pilha->V = (tPeca*) malloc(NUM_PECAS * sizeof(tPeca)); // alocação dinâmica

    if (pilha->V == NULL) // caso tenha erro para alocar memória
        return false; //Não conseguiu alocar
    else
        return true;  //Conseguiu alocar
}

// ***********************************************
// ******                                   ******
// ***********************************************
void limpaPilha(tPilha* pilha) {
    pilha->topo = -1;
    free(pilha->V);
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool empilha(tPilha** pilha, tPeca peca) {
    if ((**pilha).topo < NUM_PECAS - 1) {
        (**pilha).topo++;
        (**pilha).V[(**pilha).topo] = peca;
        return true;
    } else {
        return false;
    }
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool desempilha(tPilha* pilha, tPeca* peca) {
    if (pilha->topo > -1) {

        //Retornando a peca do topo
        peca->esquerda = pilha->V[ pilha->topo ].esquerda;
        peca->direita = pilha->V[ pilha->topo ].direita;

        pilha->topo--; // decrementa a variavel que controla o "tamanho" da pilha
        return true;
    }
    else
        return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void mostraTopoPilha(tPilha pilha) {
    imprimePeca(pilha.V[pilha.topo]);
}
