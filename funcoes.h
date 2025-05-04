#ifndef _FUNCOES_H
#define _FUNCOES_H

// Tipos de dados
typedef enum { NATUREZA, CULTURAL, FESTIVO, RELAXANTE } Tag;

// Lista circular de atrações
typedef struct atracoes {
    char atracao[40];
    Tag categoria;
    char descricao[100];
    char descricaoHorario[50];
    int pontuacao;              // pontuação acumulada
    struct atracoes *prox;
    struct atracoes *ant;
} Atracoes;

// Controlador da lista de atrações (descritor)
typedef struct descritor {
    Atracoes *cauda;
    int quantidade;
} Descritor;

// Lista duplamente encadeada de cidades
typedef struct cidades {
    char cidade[30];
    Descritor *atracao;         // descritor da lista circular de atrações
    struct cidades *prox;
    struct cidades *ant;
} Cidades;

// Informações sobre a viagem do usuário
typedef struct viagem {
    Cidades *cidade;
    int duracaoEstadia;
} Viagem;

// Protótipos de funções

// Cria lista vazia de cidades
Cidades* criaListaVazia();

// Insere nova cidade no início da lista de cidades
void inserirnoInicioCidade(Cidades **lista, Cidades novaCidade);

// Insere nova atração no final da lista circular de atrações
void inserirAtracao(Descritor *d, Atracoes novaAtracao);

// Carrega cidades e atrações a partir de arquivo texto
void carregarDados(Cidades **listaCidades);

// Impressão das cidades (sem atrações)
void listarCidades(Cidades *lista);

// Impressão das cidades e suas atrações
void listarCidadesComAtracoes(Cidades *lista);

// Busca cidade pelo nome
Cidades* buscarCidade(Cidades *lista, const char *nome);

// Define cidade e duração da viagem
void definirViagem(Viagem *viagem, Cidades *cidade, int dias);

// Aplica questionário de perfil para definir pontuações
void aplicarQuestionario(int *natureza, int *cultural, int *festivo, int *relaxante);

// Aplica pontuações às atrações conforme as respostas
void aplicarPontuacaoNasAtracoes(Descritor *d, int natureza, int cultural, int festivo, int relaxante);

// Ordena atrações por pontuação (descendente)
void ordenarAtracoesPontuacao(Descritor *d);

// Remove cidade da lista de cidades
void removerCidade(Cidades **lista, const char nome[]);

// Remove atração da lista circular de atrações
void removerAtracao(Descritor *d, const char nome[]);

//Imprime as atrações personalizadas para a viagem
void imprimeRoteiroPersonalizado(Cidades *lista, Viagem *listaViagem);

//libera a memoria dedicada para as cidades e atracoes
void liberarMemoria(Cidades *listaCidades);

//abre o menu administrativo
void menuAdministrativo(Cidades **lista);

//mostra o ranking das atracoes baseado na pontuacao
void mostrarRanking(Descritor *d);

#endif 
