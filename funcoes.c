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