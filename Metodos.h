#ifndef ___METODOS___
#define ___METODOS___

//*********************************************************************
/* Possibilida o jogador escolher uma peça */
/* Caso ele escolha uma peça inválida, obrigatoriamente ele comprará uma nova. */
tPeca escolhePeca(tListaSimplesEncadeada* mesa, tListaSimplesEncadeada* lista, char* nomeJogador, bool primeiraJogada, bool esquerda, bool inicio);

//*********************************************************************
/* valida se a peça escolhida pode ser jogada */
bool validaPeca(tListaSimplesEncadeada* mesa, tPeca peca) ;

//*********************************************************************
/* muda a variável index para o número do proximo jogador */
void proximoJogador(int* index, int numJogadores);

//*********************************************************************
/* loop do jogo */
int loopJogo(int j, int numeroJogadores, tListaSimplesEncadeada* Mesa, int enderecoJogador, tJogador *jogadores, tPeca *pecaBuffer, tPilha *pedrasCompraveis);

//*********************************************************************
/* Valida se pode inserir no início da lista */
bool validaInsercaoInicio(tListaSimplesEncadeada* mesa, tPeca *peca);

//*********************************************************************
/* Valida se precisa girar a peça */
bool verificaNecessidadeInversao(tListaSimplesEncadeada* mesa, tPeca *peca);

//*********************************************************************
/* Confere a soma de pontos de forma a achar o vencedor da partida */
int conferePontos(tJogador J[], int numJogadores);

//*********************************************************************
/* Verifica se o usuário deseja simular uma nova partida */
bool perguntaSeQuerBis();

//*********************************************************************
/* Anuncia o jogador vencedor */
void anunciaVencedor(int j, int numeroJogadores, char *nomeJogador);

//*********************************************************************
/* Busca número do jogador que deve iniciar a partida */
int buscaIniciante(tJogador jogadores[], int numJogadores);

//*********************************************************************
/* Obtem o número de jogadores */
int perguntaNumeroJodagores();

//*********************************************************************
/* Obtem o nome do jogador */
char *perguntaNomeJogador(int numeroJogador);

//*********************************************************************
/* Imprime dados de um jogador específico */
void imprimeDadosJogador(tJogador *jogadores, int numeroJogador);

//*********************************************************************
/* Gera uma associação de pecas embaralhadas na pilha */
void embaralhaPecas(tPilha* ape);

//*********************************************************************
/* Ordena a lista da mão do jogador de acordo com o somatório dos numeros das peças */
void ordenaMaoJogador(tListaSimplesEncadeada lista);

//*********************************************************************
/* Limpa a tela */
void clear(void);

//*********************************************************************
/* Exibe titulo */
void mostraTitulo();

//*********************************************************************
/* Método para informar erro */
void erro(void);

#endif // ___METODOS___