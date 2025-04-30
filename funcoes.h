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
    int pontuacao;        // pontuação acumulada
    struct atracoes *prox;
    struct atracoes *ant;
} Atracoes;

// Lista duplamente encadeada de cidades
typedef struct cidades {
    char cidade[30];
    Atracoes *atracao;    // lista circular de atrações
    struct cidades *prox;
    struct cidades *ant;
} Cidades;

// Informações sobre a viagem do usuário
typedef struct viagem {
    Cidades *cidade;
    int duracaoEstadia;
} Viagem;

// Controlador da lista de atrações (opcional)
typedef struct descritor {
    Atracoes *cauda;
    int quantidade;
} Descritor;

// Protótipos de funções

// Carrega cidades e atrações a partir de arquivo texto
void carregarDados(Cidades **listaCidades);

// Impressão das cidades (sem atrações)
void listarCidades(Cidades *lista);

// Impressão das cidades e suas atrações
void listarCidadesComAtracoes(Cidades *lista);

// Questionário para determinar perfis de pontuação
void aplicarQuestionario(int *natureza, int *cultural, int *festivo, int *relaxante);

// Aplica pontuações às atrações conforme as respostas
void aplicarPontuacaoNasAtracoes(Atracoes *lista, int natureza, int cultural, int festivo, int relaxante);

// Cria lista vazia de cidades
Cidades* criaListaVazia();

// Insere nova cidade no início da lista de cidades
void inserirnoInicioCidade(Cidades **lista, Cidades novaCidade);

// Insere nova atração no final da lista circular de atrações
void inserirAtracao(Atracoes **lista, Atracoes novaAtracao);

// Busca cidade pelo nome
Cidades* buscarCidade(Cidades *lista, const char *nome);

// Define cidade e duração da viagem
void definirViagem(Viagem *viagem, Cidades *cidade, int dias);

// Ordena atrações por pontuação (descendente), alterando a lista
void ordenarAtracoesPorPontuacao(Atracoes **lista);
