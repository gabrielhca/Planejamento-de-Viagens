#ifndef _FUNCOES_H
#define _FUNCOES_H

typedef enum { NATUREZA, CULTURAL, FESTIVO, RELAXANTE } Tag;

// Lista circular de atrações
typedef struct atracoes {
    char atracao[40];
    Tag categoria;
    char descricao[100];
    char descricaoHorario[100];
    int pontuacao; // vai acumulando com as respostas
    struct atracoes *prox;
    struct atracoes *ant;
} Atracoes;

// Lista duplamente encadeada
typedef struct cidades{
    char cidade[30];
    Atracoes* atracao; // ponteiro para a lista circular
    struct cidades *prox;
    struct cidades *ant;
} Cidades;
//na funcao linkarAtracaoCidade, tem esse tipo, porem n foi criado ent eu criei pra compilar.
typedef struct cidadeAtracao {
    struct cidades* cidade;
    struct atracoes* atracao;
    struct cidadeAtracao* prox;
} CidadeAtracao;
// Informações sobre a viagem do usuário
typedef struct viagem {
    Cidades* cidade;
    int duracaoEstadia;
} Viagem;

// Controlador da lista de atrações
typedef struct descritor {
    Atracoes *cauda;
    int quantidade;
} Descritor;

//carrega dados do arquivo cidades-atracoes.txt
void carregarDados(Cidades **listaCidades);
//lista as cidades carregadas
void listarCidadesComAtracoes(Cidades *lista);
// funções que personalizam a experiencia do usuario
void aplicarQuestionario(int *natureza, int *cultural, int *festivo, int *relaxante);
void aplicarPontuacaoNasAtracoes(Atracoes *lista, int natureza, int cultural, int festivo, int relaxante);

#endif
