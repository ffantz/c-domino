#include "Domino.h"

// ***********************************************
// ******                                   ******
// ***********************************************
void imprimePeca(tPeca peca) {
  printf("[%d|%d] ", peca.esquerda, peca.direita);
}

// ***********************************************
// ******                                   ******
// ***********************************************
void invertePeca(tPeca* peca) {
    tPeca pecaTemporaria;
    pecaTemporaria.direita   = peca->direita;
    pecaTemporaria.esquerda  = peca->esquerda;

    peca->esquerda = pecaTemporaria.direita;
    peca->direita  = pecaTemporaria.esquerda;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool comparaPedra(tPeca rock1, tPeca rock2) {
    if (rock1.esquerda == rock2.esquerda) {
        if (rock1.direita == rock2.direita) {
            return true;
        }
    }
    return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int somaPeca(tPeca peca) {
    return (peca.direita + peca.esquerda);
}


