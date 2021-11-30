/* Comentários sobre as estruturas nos arquivos ".h" */

/* ----------------------*/
/* ------ HEADERS--------*/
/* ----------------------*/

//Estuturas de dados utilizadas
#include "ListaSimplesmenteEncadeada.h" //Pedras na mesa
#include "Pilha.h" //Pedras a serem compradas
#include "Metodos.h" //Metodos comuns para o funcionamento do jogo

int main() {
    tPilha pecasCompraveis;      // pilha de pecas disponiveis para compra
    tListaSimplesEncadeada Mesa; // lista de pecas da mesa
    tJogador* jogadores;         // estrutura de jogadores

    //Variáveis
    int i, j, enderecoJogador, vencedor;
    tPeca pecaBuffer;
    bool continuar; // jogar novamente

    clear(); // limpa a tela
    do {
        initPilha(&pecasCompraveis); // inicializa a pilha de pecas
        initListaSimples(&Mesa);     // inicializa a lista da mesa
        mostraTitulo();              // exibe titulo introdutorio

        int numeroJogadores = perguntaNumeroJodagores(); // metodo responsavel por definir a quantidade de jogadores para alocar a estrutura dinamicamente
        jogadores = (tJogador *) malloc(numeroJogadores * sizeof(tJogador)); // aloca dinamicamente a estrutura de jogadores de acordo com a quantidade definida

        if (jogadores != NULL) {
            //Inicia os jogadores
            for (i = 0 ; i < numeroJogadores ; i++)
            {
                initListaSimples(&jogadores[i].lista);                    // inicializa a lista de peça de cada jogador
                char *nomeJogador = perguntaNomeJogador(i + 1);           // define o nome do jogador
                jogadores[i].nome = (char *) malloc(sizeof(nomeJogador)); // aloca dinamicamente o tamanho da string do nome do jogador
                jogadores[i].nome = nomeJogador;                          // salva o nome do jogador
            }

            // Inicia jogo
            embaralhaPecas(&pecasCompraveis);  // metodo responsavel por misturar as pecas geradas

            //Distribuir pecas
            printf(" Distribuindo pecas...\n");
            while ( tamListaSimples(jogadores[0].lista) != MAX_MAO ) { // enquanto o tamanho da lista de peças de cada jogador for diferente do maximo por jogador
                for (i = 0 ; i < numeroJogadores; i++) {
                    desempilha(&pecasCompraveis, &pecaBuffer); // retira a primeira peça da pilha e define no "buffer"
                    insereOrdenadoListaSimples(&jogadores[i].lista, pecaBuffer); // insere na lista de peças do jogador de forma ordenada
                }
            }

            for (i = 0 ; i < numeroJogadores ; i++) {
                printf("\n Essas sao as pecas do %s \n ", jogadores[i].nome);
                imprimeListaSimples(jogadores[i].lista); // exibe a lista de peças dos jogadores
            }

            printf(" \nAperte enter para comecar.");
            getchar(); //pause
            clear();   // limpa a tela
            printf(" O primeiro a jogar vai ser o de maior peca: \n");

            //Faz a primeira jogada, procurando o maior peça
            enderecoJogador = buscaIniciante(jogadores ,numeroJogadores); // busca o jogador iniciante
            printf("\n O primeiro jogador eh %s\n", jogadores[enderecoJogador].nome);

            bool esquerda, inicio; // variaveis de controle para inverter a peca e colocar ela no inicio ou final da mesa

            // pergunta o jogador qual peça quer jogar
            pecaBuffer = escolhePeca(&Mesa, &jogadores[enderecoJogador].lista, jogadores[enderecoJogador].nome, true, &esquerda, &inicio); // para jogo automatico, comentar essa linha
            // pecaBuffer = removeElementoPosListaSimples(&jogadores[enderecoJogador].lista, 0); // para jogo automatico, descomentar essa linha

            if (!insereInicioListaSimples(&Mesa, pecaBuffer)) erro(); // caso nao tenha conseguido inserir a peça na lista da mesa, exibe mensagem de erro
            printf(" Jogador %s - Coloco a peca ", jogadores[enderecoJogador].nome);
            imprimePeca(pecaBuffer); // imprime a peca escolhida

            // loop do jogo ate que se encerre por pontos ou peças finalizadas
            vencedor = loopJogo(j, numeroJogadores, &Mesa, enderecoJogador, jogadores, &pecaBuffer, &pecasCompraveis);

            anunciaVencedor(j, numeroJogadores, jogadores[vencedor].nome); // Anuncia o vencedor do jogo
            getchar();

            // Limpando as listas e a pilha
            limpaPilha(&pecasCompraveis);
            limpaListaSimples(&Mesa);
            for (i = 0 ; i < numeroJogadores ; i++)
                limpaListaSimples(&jogadores[i].lista); // limpa a lista de peças dos jogadores
        } else {
            continuar = false; // erro ao alocar memória para estrutura de jogadores
            erro();            // exibe mensagem de erro
        }

        continuar = perguntaSeQuerBis(); // metodo responsavel se deseja jogar novamente
        clear();
    } while (continuar); // enquanto o usuario quiser jogar novamente

    printf(" Volte sempre!\n\n");

    return 1;
}