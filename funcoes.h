#ifndef _FUNCOES_H
#define _FUNCOES_H

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct horario{
    int horas;
    int minutos;
} Horario;

// circular
typedef struct atracoes{
    char atracao[40];
    Data periodo;
    Horario horaInicio;
    Horario horaFim;
    struct atracoes *prox;
} Atracoes;

// duplamente encadeada
typedef struct cidades{
    char cidade[30];
    Atracoes* atracao;
    struct cidades *prox;
    struct cidades *ant;
} Cidades;

typedef struct regioesBrasil {
    char regiao[30];
    Cidades cidade;
};

typedef struct viagem {
    Cidades* cidade;
    data chegada;
    Horario horaChegada;
    data saida;
    Horario horaPartida;
} Viagem;

typedef struct descritor {
    Atrações *cauda;
    int quantidade;
} Descritor;

#endif