#ifdef __unix__
#define clrscr() printf("\x1B[2J")
#elif __BORLANDC__ && __MSDOS__
#include <conio.h>
#elif __WIN32__ || _MSC_VER
#define clrscr() system("cls")
#else
#define clrscr() printf("clrscr() - Error!!\n")
#endif

#include "ListaSimplesmenteEncadeada.h" //Pedras na mesa
#include "Pilha.h" //Pedras a serem compradas
#include "Metodos.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* ------------------------------------------------------------------------------------------*/
/* --------------------- FUNÇOES COMPLEMENTARES---------------------------------------------*/
/* ----------------------------------------------------------------------------------------*/

// ***********************************************
// ******                                   ******
// ***********************************************
tPeca escolhePeca(tListaSimplesEncadeada* mesa, tListaSimplesEncadeada* lista, char* nomeJogador, bool primeiraJogada, bool esquerda, bool inicio) {
    printf("\n Essas sao as pecas do %s \n ", nomeJogador);
    ordenaMaoJogador(*lista);
    imprimeListaSimples(*lista);

    int posicaoPeca = 0;
    do {
        printf("\n %s, escolha uma peca para jogar, digitando o numero dela \n ", nomeJogador);
        scanf("%d%*c", &posicaoPeca);
    } while(posicaoPeca < 1 || posicaoPeca > tamListaSimples(*lista)); // Enquanto ele escolher um indice inexistente

    tNoSimples* peca = lista->inicio;
    int i = 1;
    for (i = 1; i < posicaoPeca; i++) { // contador simples para chegar na peça escolhida
        peca = peca->prox;
    }

    int pontas[2];
    pontas[0] = peca->V.esquerda; // extremidades da peça para comparacao
    pontas[1] = peca->V.direita;  // extremidades da peça para comparacao

    // caso seja a primeira jogada para inicializar a mesa, não é preciso fazer validação de peça possível de jogar
    if (primeiraJogada) {
        removeElementoListaSimples(lista, pontas, &esquerda, &inicio, &peca->V); // remove a peça da lista do jogador
        return peca->V;
    } else {
        if (validaPeca(mesa, peca->V)) { // testa se a peça escolhida pode ser jogada
            removeElementoListaSimples(lista, pontas, &esquerda, &inicio, &peca->V); // remove a peça da lista do jogador
            return peca->V;
        } else {
            tPeca pecaZerada;        //
            pecaZerada.direita = -1; // retorna uma peça com índice negativo para tratamento no loop do jogo
            return pecaZerada;       //
        }
    }
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool validaPeca(tListaSimplesEncadeada* mesa, tPeca peca) {
    tPeca pecaInicio = mesa->inicio->V;
    tPeca pecaFinal = mesa->final->V;

    // valida se a peça escolhida encaixa de algum lado, em alguma extremidade da mesa
    if (pecaInicio.esquerda != peca.direita
        && pecaInicio.esquerda != peca.esquerda
        && pecaFinal.direita != peca.esquerda
        && pecaFinal.direita != peca.direita) {
        return false;
    }
    return true;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void proximoJogador(int* index, int numJogadores) {
    if (*index == (numJogadores - 1))
        *index = 0;
    else
        (*index)++;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int loopJogo(int j, int numeroJogadores, tListaSimplesEncadeada *Mesa, int enderecoJogador, tJogador *jogadores, tPeca *pecaBuffer, tPilha *pecasCompraveis) {
    /* -----Loop Jogadas------------------------------------------------------------- */

    //bool esquerda  ==> true para se o lado a ser colocado é peca.esquerda
    //bool inicio    ==> true para se a peca deve ser colocada no inicio da mesa

    //bool esquerda  ==> false para se o lado a ser colocado é peca.direita
    //bool inicio    ==> false para se a peca deve ser colocada no final da mesa

    //Nessa variável, serão colocadas as pontas livres da mesa
    bool flag = true;
    bool *esquerda, *inicio; // controles para jogo automático
    int p = 1; //Garante que a primeira rodada o iniciante não jogue duas vezes
    int pontas[2];
    int vencedor = 0;
    while (flag) {
        j = 0; //Contador de pessoas que não possuem pecas pra jogar e não existe mais pecas compraveis
        int i = p;
        for (i; i < numeroJogadores ; i++) {
            pontas[0] = Mesa->inicio->V.esquerda; // define o array de pontas como cada extremidade da mesa
            pontas[1] = Mesa->final->V.direita;   // define o array de pontas como cada extremidade da mesa
            proximoJogador(&enderecoJogador, numeroJogadores); //Atualiza endereço do proximo jogador

            //Imprime a mesa
            printf("\n Essas sao as pecas da mesa\n ");
            imprimeListaSimples(*Mesa); // mostra as peças da mesa

            // jogador escolhe a peça. Caso ele escolha uma peça inválida, obrigatoriamente ele comprará uma nova.
            *pecaBuffer = escolhePeca(Mesa, &jogadores[enderecoJogador].lista, jogadores[enderecoJogador].nome, false, esquerda, inicio); // para jogo automatico, comentar essas duas linhas
            if (pecaBuffer->direita > -1) {                                                                                               // para jogo automatico, comentar essas duas linhas
            // if (removeElementoListaSimples(&jogadores[enderecoJogador].lista, pontas, &esquerda, &inicio, pecaBuffer)) { // para jogo automatico, descomentar essa linha
                printf("\n Jogador %s - Coloco a peca ", jogadores[enderecoJogador].nome);
                imprimePeca(*pecaBuffer);

                if (verificaNecessidadeInversao(Mesa, pecaBuffer)) // valida se precisa girar a peça (trocar os numeros de lado)
                    invertePeca(pecaBuffer);                       // inverte o lado da peça

                if (validaInsercaoInicio(Mesa, pecaBuffer)) // valida se a extremidade direita da peça bate com a extremidade esquerda da mesa. Se nao, deve ser inserida no final da mesa
                    insereInicioListaSimples(Mesa, *pecaBuffer);
                else
                    insereFinalListaSimples(Mesa, *pecaBuffer);
            } else{  // A peça escolhida é inválida e o jogador comprará uma nova
                if (desempilha(pecasCompraveis, pecaBuffer)) { // se tiver peça disponível para compra
                    insereOrdenadoListaSimples(&jogadores[enderecoJogador].lista, *pecaBuffer); // insere a peça comprada na lista de peças do jogador
                    printf("\n Jogador %s - Nao tenho peca! vou comprar uma.", jogadores[enderecoJogador].nome);
                }
                else{
                    printf("\n Jogador %s - Nao tenho peca e nao existe mais peca pra comprar", jogadores[enderecoJogador].nome);
                    j++; // variavel de controle para pontuacao
                }
            }
        }
        printf("\n");

        //Imprime a mesa
        printf("\n Essas sao as pecas da mesa\n ");
        imprimeListaSimples(*Mesa); // imprime pecas da mesa

        //Imprime a proxima peça da pilha de compra
        if (pecasCompraveis->topo > -1) {
            printf("\n Essa eh a proxima peca a ser comprada: ");
            mostraTopoPilha(*pecasCompraveis); // exibe a primeira peca da pilha
            printf("\n");
        }
        else
            printf("\n Nao ha mais pecas para compra \n");

        //Imprime a mão dos jogadores
        for (i = 0; i < numeroJogadores; i++) {
            printf("\n Essas sao as pecas do jogador %s \n ", jogadores[i].nome);
            imprimeListaSimples(jogadores[i].lista);
        }
        printf("\n\n aperte enter para ver a proxima rodada");
        getchar();
        clear();

        //Verifica se algum jogador já venceu
        for (i = 0; i < numeroJogadores; i++) {
            proximoJogador(&enderecoJogador, numeroJogadores);
            if (tamListaSimples(jogadores[enderecoJogador].lista) == 0) {
                flag = false;
                vencedor = enderecoJogador;
                break;
                /*Com parada forçada, garantimos que o primeiro
                jogador a terminar as pedras vai ser o ganhador */
            }
        }

        //Verifica se todos os jogadores não possuem peças para jogar
        if (j == numeroJogadores) {
            printf("\n Nao ha mais jogadas possiveis");
            vencedor = conferePontos(jogadores,numeroJogadores); //Quem tem mais pontos ganha
            flag = false;
        }
        p = 0;
    }

    return vencedor;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool validaInsercaoInicio(tListaSimplesEncadeada* mesa, tPeca *peca) {
    tPeca pecaInicio = mesa->inicio->V;
    tPeca pecaFinal = mesa->final->V;

    // caso a peça esteja batendo com a extremidade da esquerda da mesa
    if (pecaInicio.esquerda == peca->direita) {
        return true;
    }
    return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool verificaNecessidadeInversao(tListaSimplesEncadeada* mesa, tPeca *peca) {
    tPeca pecaInicio = mesa->inicio->V;
    tPeca pecaFinal = mesa->final->V;

    // Valida se as extremidades da mesa batem com o "lado" que a peça se encontra
    if ((pecaInicio.esquerda != peca->direita && pecaInicio.esquerda == peca->esquerda)
        || (pecaFinal.direita != peca->esquerda && pecaFinal.direita == peca->direita)) {
        return true;
    }
    return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int conferePontos(tJogador jogadores[], int numJogadores) {
    int i = 0, j = 1, winner = 0;

    //Busca maior valor do somatório de pedras
    while (j < numJogadores) {
        if (somaListaSimples(jogadores[i].lista) < somaListaSimples(jogadores[j].lista)) {
            winner = j;
            i = j;
            j++;
        }
        else j++;
    }

    return winner;
}

// ***********************************************
// ******                                   ******
// ***********************************************
bool perguntaSeQuerBis() {
    char resposta;
    bool bandeira;

    do{
        printf("\n\n Deseja realizar outra partida? [Y/N]\n");
        scanf("%c%*c", &resposta);
        resposta = tolower(resposta); // transforma o caractere de entrada em letra minúscula para facilitar casos de teste (assim o usuario pode digitar n, N, y ou Y)
        bandeira = (resposta != 'y') && (resposta != 'n');
        if (bandeira)
            printf(" Nao entendi...");

    }
    while (bandeira);

    if (resposta == 'y')
        return true;
    else
        return false;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void anunciaVencedor(int j, int numeroJogadores, char *nomeJogador){
    if (j == numeroJogadores)
            printf("\n\n Parabens %s, voce ganhou por ter mais pontos!!!", nomeJogador);
        else
            printf("\n\n Parabens %s, voce ganhou por ter jogado todas as pedras!!!\n", nomeJogador);
}

// ***********************************************
// ******                                   ******
// ***********************************************
int buscaIniciante(tJogador jogadores[], int numJogadores) {
    int i = 0, j = 1, iniciante = 0;
    tPeca pedras[numJogadores];
    for (i=0 ; i < numJogadores ; i++) {
        pedras[i].direita = jogadores[i].lista.inicio->V.direita;
        pedras[i].esquerda = jogadores[i].lista.inicio->V.esquerda;
    }

    i = 0;

    //Busca maior valor entre as maiores encontradas em cada mão
    while (j<numJogadores) {
        if (somaPeca(pedras[i]) == somaPeca(pedras[j])) {
            if (pedras[i].direita < pedras[j].direita) { //Na soma igual, Direita vence
                iniciante = j;
                i = j;
                j++;
            }
            else j++;
        }
        else if (somaPeca(pedras[i]) < somaPeca(pedras[j])) {
            iniciante = j;
            i = j;
            j++;
        }
        else j++; //Se somaPeca(pedras[i]) for maior
    }

    return iniciante;
}

// ***********************************************
// ******                                   ******
// ***********************************************
int perguntaNumeroJodagores() {
    int numJogadores = 0;
    bool numeroInvalido;

    do{
        printf("\nQuantas pessoas vao jogar?\n");
        scanf("%d%*c", &numJogadores);
        numeroInvalido = (numJogadores < 2) || (numJogadores > 4) || (numJogadores == 3); // teste de quantidade inválida de jogadores
        if (numeroInvalido)
            printf(" So eh possivel jogar de 2 ou 4 pessoas!");

    }
    while (numeroInvalido); // enquanto a entrada for inválida

    return numJogadores;
}

// ***********************************************
// ******                                   ******
// ***********************************************
char *perguntaNomeJogador(int numeroJogador) {
    int c;
    char *nome = malloc (sizeof(char));
    bool nomeValido;

    nome[0] = '\0';

    do{
        printf("\n Jogador %d, qual seu nome?\n", numeroJogador);
        int i = 0;
        for(i; i < 100 && (c = getchar()) != '\n' && c != EOF; i++)
        {
            nome        = realloc(nome, (i + 2) * sizeof(char)); // realocando memoria
            nome[i]     = (char) c; // cast de int para char
            nome[i + 1] = '\0'; // inserindo caractere 'null' no fim da string
        }

        nomeValido = strcmp(nome, "");
        if (!nomeValido)
            printf(" Informe um nome!");

    } while (!nomeValido);

    return nome;
}

// ***********************************************
// ******                                   ******
// ***********************************************
void imprimeDadosJogador(tJogador *jogadores, int numeroJogador) {
    printf("\n %s, essas sao suas pecas: ", jogadores[numeroJogador].nome);
}

// ***********************************************
// ******                                   ******
// ***********************************************
void embaralhaPecas(tPilha* ape) {
    srand ( time(NULL) );

    tPeca unid;
    tListaSimplesEncadeada pecas;
    int j,k;

    initListaSimples(&pecas);

    //Gera as peças
    printf("\n Gerando as pecas...\n");
    for (j=0 ; j<7 ; j++) {          //Linha de peças
        for (k=0 ; k<=j ; k++) {    //Coluna de peças
            unid.esquerda = k;
            unid.direita = j;
            if (!insereInicioListaSimples(&pecas,unid))
                erro();
        }
    }
    imprimeListaSimples(pecas);

    //Colocando na pilha de forma aleatória
    printf("\n Embaralhando...\n");
    while (tamListaSimples(pecas)>0) {
        int index = rand();
        index = index % tamListaSimples(pecas);
        unid = removeElementoPosListaSimples(&pecas,index);
        empilha(&ape, unid);
    }

    limpaListaSimples(&pecas);
}

// ***********************************************
// ******                                   ******
// ***********************************************
void ordenaMaoJogador(tListaSimplesEncadeada lista)
{
    tNoSimples* atual = lista.inicio;

    // Loop entre todos os elementos para performar troca
    while (atual != NULL) {
        tNoSimples* proximo = atual->prox;
        tNoSimples* aux = atual;
        while (proximo != NULL) {
            int somaAtual, somaProx = 0;
            somaAtual = atual->V.esquerda + atual->V.direita;
            somaProx  = proximo->V.esquerda + proximo->V.direita;

            if (somaProx > somaAtual) {
                atual->V.esquerda = proximo->V.esquerda;
                atual->V.direita  = proximo->V.direita;

                proximo->V.esquerda = aux->V.esquerda;
                proximo->V.direita  = aux->V.direita;
            }
            proximo = proximo->prox;
        }
        atual = atual->prox;
    }
}

// ***********************************************
// ******                                   ******
// ***********************************************
void clear(void) {
    clrscr(); // metodo responsável por limpar a tela
}

// ***********************************************
// ******                                   ******
// ***********************************************
void mostraTitulo() {
    clear(); // limpa a tela
    printf("--------------DOMINO --------------------\n");
    printf("------------por: Fantz ------------------\n");
    printf("   ___________\n");
    printf("  |    .|.   .|\n");
    printf("  |  .  |  .  |\n");
    printf("  |.    |.   .|\n");
    printf("  |_____|_____|\n\n");
}

// ***********************************************
// ******                                   ******
// ***********************************************
void erro(void) {
    printf("\nOcorreu um erro durante a execucao\n");
    exit(1);
}