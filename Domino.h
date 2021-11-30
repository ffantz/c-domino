#ifndef ___DOMINO___
#define ___DOMINO___

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define NUM_PECAS 28 //Número de pedras no jogo
#define MAX_MAO 6 //Número de pedras que começam na mão do jogador

/* Peça */
typedef struct Peca {
    int esquerda;
    int direita;
} tPeca;

/*
    ___________
   |          |
   |    O     |  => esquerda
   |__________|                Exemplo para quina de ás
   |  O    O  |                       ( 1 | 5 )
   |     O    |  => direita
   |___O___O__|

Peca.esquerda = 1
Peca.direita = 5
*/

/* Quando que uma pedra é maior que a outra?
    - Se o lado direito for maior
    - So o direito for igual, compara-se o esquerdo

    - O lado esquerdo, nessa lógica, sempre será um valor
    menor ou igual comparando com o lado direito

    - Isso implica que a função invertePeca só podera ser usada
    para colocar uma pedra na mesa no seu lado certo.

    (ESQUERDA <= DIREITA)
*/

/* ------------------------------------------------------------------*/
/* --------------------- CABEÇALHO FUNÇOES DOMINÓ--------------------*/
/* ------------------------------------------------------------------*/

// ***********************************************
/*Imprime a pedra passada como parâmetro*/
void imprimePeca(tPeca rock);

// ***********************************************
/*Inverte a pedra passada como parâmetro*/
void invertePeca(tPeca* rock);

// ***********************************************
/*Compara o conteúdo interno de duas pedras*/
bool comparaPedra(tPeca rock1, tPeca rock2);

/* Realiza soma dos valores esqueda e direita da pedra */
int somaPeca(tPeca rock);

#endif // ___DOMINO___