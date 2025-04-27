#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/*Função que cria uma lista vazia do tipo cidades. Retorna NULL pois a lista é vazia*/
Cidades* criaListaVazia (){
    return NULL;
}

/*Função para inserção no inicio da CIDADE. Neste caso e como farei alterações nos dados e nos ponteiros, estou utilizando ponteiros
duplos e recebo como parametro a lista do tipo cidades e novaCidade que receberá a nova cidade a ser inserida. Faço o teste pra verificar 
se a alocação de memória foi bem sucedida, do contrário imprime-se na tela. Faço com que o ponteiro criado chamado nova receba a novaCidade
Nisso preciso realizar ajustes nos ponteiros, então o o campo ant de nova aponta para NULL, pois ela será o primeiro elemento 
da lista duplamente encadeada (não circular). Faço com que o próximo do nova aponte para para o inicio da lista em nova->prox = *lista*/
void inserirnoInicioCidade (Cidades** lista, Cidades novaCidade){
    Cidades* nova = (Cidades*)malloc(sizeof(Cidades));
    if (nova == NULL) {
        printf ("Erro na alocação de memória da Cidade!\n");
        return;
    }
    *nova = novaCidade;

    nova->ant = NULL; 
    nova->prox = *lista;

    if(*lista != NULL){
        (*lista)->ant = nova; 
    }
    *lista = nova;
}
/*Alterar depois para inserir as atrações de forma ordenada para manter organização
Basicamente a mesma estrutura do anterior, nsere uma nova atração ao final da 
lista circular duplamente encadeada. Caso a lista esteja vazia, a nova atração aponta para si mesma nos campos prox e ant*/
void inserirAtracaoOrdenada (Atracoes** lista, Atracoes novaAtracao){
    Atracoes* nova = (Atracoes*)malloc(sizeof(Atracoes));
    if (nova == NULL){
        printf ("Erro na alocação de memória da Atração!\n");
        return;
    }

    *nova = novaAtracao;

    if(*lista == NULL) {
        nova->prox = nova;
        nova->ant = nova; 
    }
    else {
        nova->ant = (*lista)->ant;
        nova->prox = *lista;
        (*lista)->ant->prox = nova;
        (*lista)->ant = nova;
        
    }

}
/*Função que vincula uma atração a uma cidade específica. Percorre ambas as listas (cidades e atrações), 
buscando pelos nomes informados. Se ambos forem encontrados, cria um nó de ligação e insere na lista de vínculos (CidadeAtracao).
Falta finalizar*/
void linkarAtracaoCidade (Cidades listaCidades, Atracoes listaAtracoes, const char* nomeCidade, const char* nomeAtracao, CidadeAtracao** listaLink){

    Cidades* cidadeAtual = listaCidades;
    Atracoes* atracaoAtual = listaAtracoes; 

    while (cidadeAtual != NULL && strcmp(cidadeAtual->cidade, nomeCidade) != 0){
        cidadeAtual = cidadeAtual->prox;
    }

    Atracoes* inicio = atracaoAtual;

}


// funções que personalizam a experiencia do usuario

void aplicarQuestionario(int *natureza, int *cultural, int *festivo, int *relaxante) {
    int resposta;

    printf("Responda com o número da opção escolhida.\n");

    // Pergunta 1
    do {
        printf("1) Você prefere passar o dia em contato com a natureza ou em um ambiente urbano cheio de opções modernas?\n");
        printf("   1 - Natureza\n   2 - Urbano\n> ");
        scanf("%d", &resposta);
        if (resposta == 1) *natureza += 5;
        else if (resposta == 2) *festivo += 5;
        else printf("Resposta incorreta. Tente novamente.\n");
    } while (resposta != 1 && resposta != 2);

    // Pergunta 2
    do {
        printf("2) Você gostaria mais de visitar um museu histórico ou curtir uma festa local?\n");
        printf("   1 - Museu\n   2 - Festa\n> ");
        scanf("%d", &resposta);
        if (resposta == 1) *cultural += 5;
        else if (resposta == 2) *festivo += 5;
        else printf("Resposta incorreta. Tente novamente.\n");
    } while (resposta != 1 && resposta != 2);

    // Pergunta 3
    do {
        printf("3) Você busca relaxar em lugares tranquilos ou viver experiências cheias de adrenalina?\n");
        printf("   1 - Tranquilos\n   2 - Adrenalina\n> ");
        scanf("%d", &resposta);
        if (resposta == 1) *relaxante += 5;
        else if (resposta == 2) *natureza += 5;
        else printf("Resposta incorreta. Tente novamente.\n");
    } while (resposta != 1 && resposta != 2);

    // Pergunta 4
    do {
        printf("4) Você se sente mais confortável em locais silenciosos ou agitados?\n");
        printf("   1 - Silenciosos\n   2 - Agitados\n> ");
        scanf("%d", &resposta);
        if (resposta == 1) *relaxante += 5;
        else if (resposta == 2) *festivo += 5;
        else printf("Resposta incorreta. Tente novamente.\n");
    } while (resposta != 1 && resposta != 2);
}

void aplicarPontuacaoNasAtracoes(Atracoes *lista, int natureza, int cultural, int festivo, int relaxante) {
    if (lista == NULL) return;

    Atracoes *inicio = lista;
    do {
        switch (lista->categoria) {
            case NATUREZA:
                lista->pontuacao += natureza;
                break;
            case CULTURAL:
                lista->pontuacao += cultural;
                break;
            case FESTIVO:
                lista->pontuacao += festivo;
                break;
            case RELAXANTE:
                lista->pontuacao += relaxante;
                break;
        }
        lista = lista->prox;
    } while (lista != inicio);
}

void carregarDados(Cidades **listaCidades) {
    FILE *arquivo = fopen("cidadesAtracoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo cidadesAtracoes.txt\n");
        return;
    }

    char nomeCidade[50];
    char nomeAtracao[50];
    int categoria;
    char descricao[100];
    char descricaoHorario[100];
    //catergoria(natureza = 0, cultural = 1, festivo = 2, relaxante = 3)
    while (fscanf(arquivo, "%99[^;];%99[^;];%d;%99[^;];%99[^\n]\n", nomeCidade, nomeAtracao, &categoria, descricao, descricaoHorario) == 5) { 

        // ve se a cidade ja existe
        Cidades* cidadeAtual = *listaCidades;
        while (cidadeAtual != NULL && strcmp(cidadeAtual->cidade, nomeCidade) != 0) {
            cidadeAtual = cidadeAtual->prox;
        }

        // se nao encontrar, cria uma nova
        if (cidadeAtual == NULL) {
            Cidades novaCidade;
            strcpy(novaCidade.cidade, nomeCidade);
            novaCidade.atracao = NULL;
            novaCidade.prox = NULL;
            novaCidade.ant = NULL;
            inserirnoInicioCidade(listaCidades, novaCidade);
            cidadeAtual = *listaCidades; // novo nó criado fica no início
        }

        //cria atracao
        Atracoes novaAtracao;
        strcpy(novaAtracao.atracao, nomeAtracao);
        novaAtracao.categoria = (Tag)categoria;
        strcpy(novaAtracao.descricao, descricao);
        strcpy(novaAtracao.descricaoHorario, descricaoHorario);
        novaAtracao.pontuacao = 0;
        novaAtracao.prox = NULL;

        inserirAtracaoOrdenada(&(cidadeAtual->atracao), novaAtracao);
    }

    fclose(arquivo);
}
