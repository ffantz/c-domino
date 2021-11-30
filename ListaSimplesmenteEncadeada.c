
#include "ListaSimplesmenteEncadeada.h"


// ***********************************************
// ******                                   ******
// ***********************************************
void initListaSimples(tListaSimplesEncadeada* lista) {
    lista->inicio = NULL; // define a lista inteiramente vazia
    lista->final = NULL;  // define a lista inteiramente vazia
    lista->numElem = 0;   // define a lista inteiramente vazia
}

// ***********************************************
// ******                                   ******
// ***********************************************
void limpaListaSimples(tListaSimplesEncadeada* lista) {
    tNoSimples* inicio = lista->inicio;
    tNoSimples* proxima = NULL;

    while (inicio != NULL) {
        proxima = inicio->prox;
        free(inicio);
        inicio = proxima;
    }

    lista->inicio = NULL;
    lista->final = NULL;
    lista->numElem = 0;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void imprimeListaSimples(tListaSimplesEncadeada lista) {
    tNoSimples* proximo = lista.inicio;

    int contador = 1;
    if (proximo != NULL) {
        while ( proximo->prox != NULL ) {
            printf("%d - ", contador);
            imprimePeca(proximo->V);
            proximo = proximo->prox;
            contador++;
        }
        printf("%d - ", contador);
        imprimePeca(proximo->V);
    } else {
        printf("Nao ha elementos na lista");
    }

    printf("\n__________________________________________________________\n");
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool insereFinalListaSimples(tListaSimplesEncadeada* lista, tPeca peca) {
    tNoSimples* aInserir = alocaNoSimples(peca);
    if (aInserir == NULL)
        return false;

    tNoSimples* ultimo = lista->final;
    if (ultimo == NULL)      //Lista vazia
        lista->inicio = aInserir;
    else                     //Lista não vazia
        ultimo->prox = aInserir;

    lista->final = aInserir;
    lista->numElem++;
    return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool insereInicioListaSimples(tListaSimplesEncadeada* lista, tPeca peca) {
    //Aloca um novo nó
    tNoSimples* aInserir = alocaNoSimples(peca);
    if (aInserir == NULL)
        return false;

    if (lista->final != NULL)   //Lista Não Vazia
        aInserir->prox = lista->inicio;
    else                        //Lista Vazia
        lista->final = aInserir;

    lista->inicio = aInserir;
    lista->numElem++;
    return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
tNoSimples* alocaNoSimples(tPeca peca) {
    tNoSimples* novo = (tNoSimples*) malloc(sizeof(tNoSimples));

    if (novo != NULL) {
        novo->V.esquerda = peca.esquerda;
        novo->V.direita = peca.direita;
        novo->prox = NULL;
    }

  return novo;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int tamListaSimples(tListaSimplesEncadeada lista) {
    return lista.numElem;
}

// ***********************************************
// ******                                   ******
// ***********************************************
tNoSimples* buscaElementoListaSimples(tListaSimplesEncadeada lista,
    tNoSimples** anterior, int pontas[], bool** esquerda, bool** inicio) {

    (**esquerda) = false; //indica se o lado da peca a ser colocado é o esquerdo
    (**inicio) = false;   //indica se deve ser colocado na ponta esquerda da mesa
    (*anterior) = NULL;      //elemento anterior ao achado
    tNoSimples* onde = lista.inicio;
    int i;

    for (i=0 ; i < 2 ; i++) {            //Alterna entre ponta esquerda e direita
        while (onde != NULL ) {         //Para caso acabe a lista
            if (onde->V.direita > pontas[i]) {       //Caso o lado direito seja maior
                if (onde->V.esquerda == pontas[i]) { //Caso o lado esquerdo seja igual
                    (**esquerda) = true;
                    if (i==0)
                        (**inicio) = true;
                    return onde;
                }
            } else if (onde->V.direita == pontas[i]) { //Caso o lado direito seja igual
                if (i==0)
                    (**inicio) = true;
                return onde;
            }
            (*anterior) = onde;
            onde = onde->prox;
        }
    }
    return NULL; //Não foi encontrado
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool insereOrdenadoListaSimples(tListaSimplesEncadeada* lista, tPeca peca) {
    tNoSimples* aInserir = alocaNoSimples(peca);

    //Não alocado
    if (aInserir == NULL) return false;

    tNoSimples* anterior = NULL;
    tNoSimples* correr= lista->inicio;

    //Lista Vazia
    if (correr == NULL) lista->inicio = aInserir;

    //Lista Não Vazia
    else {
        //Enquanto for menor ou a lista não acabar
        while (peca.direita < correr->V.direita) {
            anterior = correr;
            correr = correr->prox;
            if (correr == NULL) break;
        }

        //Ajusta o valor da posição caso o lado direito seja igual
        if ( correr != NULL) {
            if ( peca.direita == correr->V.direita ) {
                while (correr->V.esquerda > peca.esquerda) {
                    anterior = correr;
                    correr = correr->prox;
                    if (correr == NULL ) break;
                    if (peca.direita != correr->V.direita) break;
                }
            }
        }

        if (anterior == NULL) {        // Colocar na primeira posição da lista
            lista->inicio = aInserir;
            aInserir->prox = correr;
        } else if (correr == NULL) {   // Colocar no final da lista
            anterior->prox = aInserir;
        } else{                        // Meio da lista
            anterior->prox = aInserir;
            aInserir->prox = correr;
        }
    }

    lista->numElem++;
    return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool removeElementoListaSimples(tListaSimplesEncadeada* lista,
    int pontas[], bool* esquerda, bool* inicio, tPeca* peca) {

    tNoSimples* anterior;
    tNoSimples* achei = buscaElementoListaSimples(*lista, &anterior, pontas, &esquerda, &inicio); // procura o elemento na lista especificada

    if (achei == NULL) return false;

    tNoSimples* proximo = achei->prox;

    if (tamListaSimples(*lista)==1) { //O Único elemento
        lista->inicio = NULL;
    } else if (anterior == NULL) {    //Primeiro da lista
        lista->inicio = proximo;
    } else if (proximo == NULL) {     //Final da lista
        anterior->prox = proximo;
    } else{                           //Meio da lista
        anterior->prox = proximo;
    }

    *peca = achei->V; //Retornando a peca
    free(achei);
    lista->numElem--;
    return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
tPeca removeElementoPosListaSimples(tListaSimplesEncadeada* lista, int index) {

    tNoSimples* achei = lista->inicio;
    tNoSimples* anterior = NULL;
    tNoSimples* proximo = NULL;
    tPeca peca;

    //Procura ponteiro do indice especificado
    int p;
    for (p=0 ; p<index ; p++) {
        anterior = achei;
        achei = achei->prox;
    }

    if (achei == NULL) return peca;

    proximo = achei->prox;


    if (anterior == NULL) {       //Primeiro ou único da lista
        lista->inicio = achei->prox;
        if (proximo == NULL)      //Se for o unico da lista
            lista->final = NULL;
    } else if (proximo == NULL) { //Final da lista
        anterior->prox = proximo;
        lista->final = anterior;
    } else{                       //Meio da lista
        anterior->prox = proximo;

    }

    peca = achei->V;

    free(achei);
    lista->numElem--;
    return peca;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int somaListaSimples(tListaSimplesEncadeada lista) {
    int soma = 0, i;
    tNoSimples* temp = lista.inicio;
    for (i = 0 ; i < tamListaSimples(lista); i++) {
        soma = soma + somaPeca(temp->V);
        temp = temp->prox;
    }
    return soma;
}