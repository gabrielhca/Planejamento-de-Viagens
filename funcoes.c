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
void inserirAtracao(Descritor** d, Atracoes novaAtracao){
    Atracoes* nova = (Atracoes*)malloc(sizeof(Atracoes));
    if (nova == NULL){
        printf ("Erro na alocação de memória da Atração!\n");
        return;
    }

    *nova = novaAtracao;

    if(*lista == NULL) {
        nova->prox = nova;
        nova->ant = nova; 
        (*d)->cauda = nova;
        quantidade++;
    }
    else {
        nova->ant = (*d)->cauda;
        nova->prox = (*d)->cauda->prox;
        (*d)->cauda->prox = nova;
        (*d)->ant = nova;
        quantidade++;
        
    }

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
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char nomeCidade[30], nomeAtracao[40], descricao[100], descricaoHorario[50];
    int categoria;

    // Lê o arquivo linha por linha
    while (fscanf(arquivo, "%[^;];%[^;];%d;%[^;];%[^\n]\n", nomeCidade, nomeAtracao, &categoria, descricao, descricaoHorario) == 5) {
        // Verifica se a cidade já existe na lista
        Cidades *cidadeAtual = *listaCidades;
        while (cidadeAtual != NULL && strcmp(cidadeAtual->cidade, nomeCidade) != 0) {
            cidadeAtual = cidadeAtual->prox;
        }

        // Se a cidade não foi encontrada, cria uma nova cidade
        if (cidadeAtual == NULL) {
            Cidades novaCidade;
            strcpy(novaCidade.cidade, nomeCidade);
            novaCidade.atracao = NULL;
            novaCidade.prox = *listaCidades;
            novaCidade.ant = NULL;
            inserirnoInicioCidade(listaCidades, novaCidade);
            
            cidadeAtual = *listaCidades;
        }

        // Cria uma nova atração
        Atracoes novaAtracao;
        strcpy(novaAtracao.atracao, nomeAtracao);
        novaAtracao.categoria = categoria;
        strcpy(novaAtracao.descricao, descricao);
        strcpy(novaAtracao.descricaoHorario, descricaoHorario);
        novaAtracao.pontuacao = 0;  // Inicializando a pontuação como 0
        novaAtracao.prox = NULL;
        novaAtracao.ant = NULL;
        
        inserirAtracao(&cidadeAtual->atracao, novaAtracao);
        }
    }

    fclose(arquivo);
}

void listarCidades(Cidades *lista){
    if(lista == NULL){
        printf ("Nenhuma cidade cadastrada.\n");
        return;
    }

    Cidades *cidadeAtual = lista;
    while (cidadeAtual != NULL) {
        printf("Cidade: %s\n", cidadeAtual->cidade);
        cidadeAtual = cidadeAtual->prox;
        printf("\n");
    }


void listarCidadesComAtracoes(Cidades *lista) {
    if (lista == NULL) {
        printf("Nenhuma cidade cadastrada.\n");
        return;
    }

    Cidades *cidadeAtual = lista;
    while (cidadeAtual != NULL) {
        printf("Cidade: %s\n", cidadeAtual->cidade);

        if (cidadeAtual->atracao == NULL) {
            printf("  Nenhuma atração cadastrada.\n");
        } else {
            Atracoes *atracaoAtual = cidadeAtual->atracao;
            Atracoes *inicio = atracaoAtual;
            do {
                printf("  - %s (%s)\n", atracaoAtual->atracao, 
                    atracaoAtual->categoria == NATUREZA ? "Natureza" :
                    atracaoAtual->categoria == CULTURAL ? "Cultural" :
                    atracaoAtual->categoria == FESTIVO ? "Festivo" :
                    atracaoAtual->categoria == RELAXANTE ? "Relaxante" : "Desconhecido"
                );
                atracaoAtual = atracaoAtual->prox;
            } while (atracaoAtual != inicio); // porque é lista circular
        }

        printf("\n");
        cidadeAtual = cidadeAtual->prox;
    }
}

//Função para definir a viagem e a estadia. Precisa linkar com as funções de aplicação do questionário e com as funções de ordenação das atrações de acordo com
//a pontuação definida
void definirViagem(Viagem* viagem, Cidades* cidade, int dias) {
    viagem->cidade = cidade;
    viagem->duracaoEstadia = dias;

    printf("Viagem definida: %s por %d dias.\n", cidade->cidade, dias);
}


//Função para encontrar para qual cidade a pessoa irá viajar. 
Cidades* buscarCidade(Cidades* lista, char nome[]) {
    Cidades* atual = lista;

    while (atual != NULL) {          
        if (strcmp(atual->cidade, nome) == 0) {
            return atual; // Retorna a cidade encontrada
        }
        atual = atual->prox;
    }

    printf("Cidade %s não encontrada.\n", nome);
    return NULL;
}

//função para ordenar atrações por pontuação
void ordenarAtracoesPontuacao(Atracoes **lista){
    if(*lista==NULL || (*lista)->prox==*lista){
        return;
    }
Atracoes *listaOrdenada = NULL;
Atracoes *atual = *lista;
Atracoes *inicio = *lista;

do{
    Atracoes *proximo = atual->prox;

    atual->prox = atual;
    atual->ant = atual;

if (listaOrdenada == NULL) {
    listaOrdenada = atual;
} 
else {
    Atracoes *temp = listaOrdenada;
    do { 
        if(atual->pontuacao>temp->pontuacao){
            break;
        }
        temp = temp->prox;
    }while(temp != listaOrdenada);

    atual->prox = temp;
    atual->ant = temp->ant;
    temp->ant->prox = atual;
    temp->ant = atual;

    if (temp == listaOrdenada && atual->pontuacao > temp->pontuacao) {
                listaOrdenada = atual;
    }
}
    atual = proximo;
}while(atual!=inicio);
*lista = listaOrdenada;
}

void removerCidade(Cidades **lista, char nome[]){
    Cidades* remove = buscarCidade(*lista, nome[]);
    Cidades* aux = lista;

    if(remove->ant==NULL && remove->prox==NULL){
        *lista = NULL;
    }
    else if(remove->prox==NULL){
        remove->ant->prox=NULL;
    }
    else if(remove->ant==NULL){
        *lista = remove->prox;
        remove->prox->ant = NULL;
    }
    else{
        remove->prox->ant = remove->ant;
        remove->ant->prox = remove->prox;
    }
free(remove);
printf ("Cidade Removida\n");
}

void removerAtracao(Descritor **d, char nome[]){
    if(*d == NULL || (*d)->cauda == NULL){
        printf("Lista de atrações.\n");
        return;
    }

    Atracoes *inicio = (*d)->cauda->prox;
    Atracoes *atual = inicio;

    do {
        if(strcmp(atual->atracao, nome)==0{
            if(atual->prox == atual){
                free(atual);
                (*d)->cauda = NULL
            }else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                if (atual == (*d)->cauda)
                (*d)->cauda = atual->ant;
                free(atual);
            }
            (*d)->quantidade--;
            printf("Atração removida com sucesso.\n");
            return;
        }
        atual = atual->prox;
    } while (atual != inicio);

    printf ("Atração não localizada.\n");
}

    
    
