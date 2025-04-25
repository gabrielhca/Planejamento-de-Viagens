#ifndef _FUNCOES_H
#define _FUNCOES_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct horario {
    int horas;
    int minutos;
} Horario;

typedef enum { NATUREZA, CULTURAL, FESTIVO, RELAXANTE } Tag;

// Lista circular
typedef struct atracoes {
    char atracao[40];
    Tag categoria;
    int pontuacao; // vai acumulando com as respostas
    Data periodo;
    Horario horaInicio;
    Horario horaFim;
    struct atracoes *prox;
} Atracoes;


// Lista duplamente encadeada
typedef struct cidades{
    char cidade[30];
    Atracoes* atracao; // ponteiro para a lista circular
    struct cidades *prox;
    struct cidades *ant;
} Cidades;

typedef struct viagem {
    Cidades* cidade;
    data chegada;
    Horario horaChegada;
    data saida;
    Horario horaPartida;
} Viagem;

typedef struct descritor {
    Atracoes *cauda;
    int quantidade;
} Descritor;


// funções que personalizam a experiencia do usuario
void aplicarQuestionario(int *natureza, int *cultural, int *festivo, int *relaxante);
void aplicarPontuacaoNasAtracoes(Atracoes *lista, int natureza, int cultural, int festivo, int relaxante);

#endif