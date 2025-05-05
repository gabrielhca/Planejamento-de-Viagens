#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/*Função que cria uma lista vazia do tipo cidades. Retorna NULL pois a lista é vazia*/
Cidades* criaListaVazia (){
    return NULL;
}

/*Função que carrega os dados do arquivo 'cidadesAtracoes.txt', no formato: NomeCidade;NomeAtracao;Categoria;Descricao;DescricaoHorario. 
A função insere cidades e atrações na estrutura de dados conforme lidas. */
void carregarDados(Cidades **listaCidades) {
    FILE *arquivo = fopen("cidadesAtracoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char nomeCidade[30], nomeAtracao[40], descricao[100], descricaoHorario[50];
    int categoria;

    while (fscanf(arquivo, "%[^;];%[^;];%d;%[^;];%[^\n]\n", nomeCidade, nomeAtracao, &categoria, descricao, descricaoHorario) == 5) {
        Cidades *cidadeAtual = *listaCidades;
        while (cidadeAtual != NULL && strcmp(cidadeAtual->cidade, nomeCidade) != 0) {
            cidadeAtual = cidadeAtual->prox;
        }

        // Se a cidade não foi encontrada, cria e insere uma nova
        if (cidadeAtual == NULL) {
            Cidades novaCidade;
            strcpy(novaCidade.cidade, nomeCidade);
            novaCidade.atracao = NULL;
            novaCidade.prox = NULL;
            novaCidade.ant = NULL;
            inserirnoInicioCidade(listaCidades, novaCidade);
            cidadeAtual = *listaCidades; // Atualiza ponteiro
        }

        // Cria e insere nova atração
        Atracoes novaAtracao;
        strcpy(novaAtracao.atracao, nomeAtracao);
        novaAtracao.categoria = categoria;
        strcpy(novaAtracao.descricao, descricao);
        strcpy(novaAtracao.descricaoHorario, descricaoHorario);
        novaAtracao.pontuacao = 0;
        novaAtracao.prox = NULL;
        novaAtracao.ant = NULL;

        inserirAtracao(cidadeAtual->atracao, novaAtracao);
    }

    fclose(arquivo);
}

/*Função feita para imprimir todas as cidades cadastradas, sem as atrações*/
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
}

/*Função feita para imprimir todas as cidades COM as atrações.*/
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
            Atracoes *atracaoAtual = cidadeAtual->atracao->cauda;
            Atracoes *inicio = atracaoAtual;
            do {
                printf("  - %s | Descrição: %s | Horário: %s\n", 
                    atracaoAtual->atracao, atracaoAtual->descricao, atracaoAtual->descricaoHorario);
                atracaoAtual = atracaoAtual->prox;
            } while (atracaoAtual != inicio); // porque é lista circular
        }

        printf("\n");
        cidadeAtual = cidadeAtual->prox;
    }
}

//Função para definir a viagem e a estadia. 
void definirViagem(Viagem* viagem, Cidades* cidade, int dias) {
    viagem->cidade = cidade;
    viagem->duracaoEstadia = dias;

    printf("Viagem definida: %s por %d dias.\n", cidade->cidade, dias);
}

//Função para buscar para qual cidade a pessoa irá viajar. Verifica se a cidade existe na lista, se sim, retorna a cidade) 
Cidades* buscarCidade(Cidades* lista, const char *nome) {
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

// FUNÇÕES DO MENU ADMINISTRATIVO

/*abre o menu administrativo que tem as opcoes de adicionar cidade/atracao, remover cidade/atracao,*/
void menuAdministrativo(Cidades **lista) {
    char senha[25];
    printf("\nDigite a senha de acesso: ");
    scanf("%s", senha);
    
    int opcao;
    while(strcmp(senha, "123" )!=0){
        printf("Senha incorreta! Tente novamente ou digite 1 para voltar ao menu principal\n");
        scanf("%s", senha);
        if(strcmp(senha, "123")==0){
            continue;
        }
        else if(strcmp(senha, "1")==0){
            return;
        }
    }
    do {
        printf("\n\t MENU ADMINISTRATIVO \t\n");
        printf("1 - Adicionar cidade\n");
        printf("2 - Remover cidade\n");
        printf("3 - Adicionar atração.\n");
        printf("4 - Remover atração.\n");
        printf("5 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1: {
                Cidades nova;
                printf("Nome da cidade: ");
                scanf("%s", nova.cidade);
                inserirnoInicioCidade(lista, nova);
                printf("Cidade adicionada!\n");
                break;
            }
            case 2: {
                char nome[30];
                printf("Nome da cidade para remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; 
                removerCidade(lista, nome);
                break;
            }
            case 3:{
                char nomeCidade[30];
                printf("Qual o nome da cidade que a atração pertence?\n");
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                
                Cidades *cidadeEscolhida = buscarCidade(*lista, nomeCidade);
                if (!cidadeEscolhida) {
                    printf("Cidade %s não encontrada! Primeiro insira a cidade\n", nomeCidade);
                    break;
                }

                Atracoes nova;
                printf("Nome da atração: ");
                fgets(nova.atracao, sizeof(nova.atracao), stdin);
                nova.atracao[strcspn(nova.atracao, "\n")] = '\0';
                
                int categoriaAux;
                printf("Categoria (0-Natureza, 1-Cultural, 2-Festivo, 3-Relaxante): ");
                scanf("%d", &categoriaAux);
                nova.categoria = (Tag)categoriaAux;
                while (getchar() != '\n');

                printf("Descrição: ");
                fgets(nova.descricao, sizeof(nova.descricao), stdin);
                nova.descricao[strcspn(nova.descricao, "\n")] = '\0';

                printf("Horário (ex: 08:00 - 22:00): ");
                fgets(nova.descricaoHorario, sizeof(nova.descricaoHorario), stdin);
                nova.descricaoHorario[strcspn(nova.descricaoHorario, "\n")] = '\0';

                inserirAtracao(cidadeEscolhida->atracao, nova);
                printf("Atração adicionada com sucesso!\n");
                break;
                
                case 4: { // Remover atração
                char nomeCidade[30], nomeAtracao[40];
                printf("Nome da cidade onde a atração está: ");
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                
                Cidades *cidadeEscolhida = buscarCidade(*lista, nomeCidade);
                if (!cidadeEscolhida) {
                    printf("Cidade não encontrada!\n");
                    break;
                }

                printf("Nome da atração a ser removida: ");
                fgets(nomeAtracao, sizeof(nomeAtracao), stdin);
                nomeAtracao[strcspn(nomeAtracao, "\n")] = '\0';

                removerAtracao(cidadeEscolhida->atracao, nomeAtracao);
                break;
            }
                case 5: // Voltar
                printf("Voltando ao menu principal...\n");
                break;
                
                default:
                printf("Opção inválida!\n");
            }
        }
    } while (opcao != 5);
}

/*Função para inserção no inicio da cidade utilizando ponteiros duplos*/
void inserirnoInicioCidade (Cidades** lista, Cidades novaCidade){
    Cidades* nova = (Cidades*)malloc(sizeof(Cidades));
    if (nova == NULL) {
        printf ("Erro na alocação de memória da Cidade!\n");
        return;
    }
    strcpy(nova->cidade, novaCidade.cidade);
    nova->atracao = (Descritor *)malloc(sizeof(Descritor));
    if (nova->atracao == NULL) {
        printf("Erro ao alocar memória para descritor de atrações.\n");
        free(nova);
        return;
    }
    nova->atracao->cauda = NULL;
    nova->atracao->quantidade = 0;

    nova->ant = NULL; 
    nova->prox = *lista;

    if(*lista != NULL){
        (*lista)->ant = nova; 
    }
    *lista = nova;
}

/*Função para inserção de atrações. Utiliza o descritor como parametro e a lista de atrações. Faz a inserção no final da lista circular de atraçóes.*/
void inserirAtracao(Descritor *d, Atracoes novaAtracao){
    Atracoes *nova = malloc(sizeof(Atracoes));
    if (!nova){
        printf("Erro na alocação de memória da Atração!\n");
        return;
    }

    *nova = novaAtracao;
    nova->prox = nova->ant = NULL;

    if (d->cauda == NULL) {
        // Lista vazia: nova aponta para si mesma
        nova->prox = nova->ant = nova;
        d->cauda = nova;
    } else {
        // Insere após a cauda atual (fim da lista circular)
        Atracoes *primeiro = d->cauda->prox;
        nova->prox = primeiro;
        nova->ant = d->cauda;
        d->cauda->prox = nova;
        primeiro->ant = nova;
        d->cauda = nova;       // nova vira a nova cauda
    }

    d->quantidade++;  // incrementa o total
}

/*Função de remover cidade, utiliza como parametro lista do tipo Cidades e nome, para que possamos buscar a cidade. reaproveitamos a função de buscarCidade
para poder localizar e retornar a cidade que queremos remover.*/
void removerCidade(Cidades **lista, const char nome[]){
    Cidades* remove = buscarCidade(*lista, nome);
    if(remove == NULL){
        return;
    }
    
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

/*Função de remover atração. Utilizamos o descritor criado e nome para poder buscar a atração que desejamos fazer a remoção. É feito o processo de remoção
de acordo com a localidade da atração. Se a atração estiver no inicio da lista, reajustamos o ponteiro da cauda e do segundo item(novo primeiro), se estiver
no final, reajustamos ponteiro do penultimo elemento (novo ultimo) e do primeiro elemento. */
void removerAtracao(Descritor *d, const char *nome) {
    if (d == NULL || d->cauda == NULL) {
        printf("Lista de atrações vazia.\n");
        return;
    }

    Atracoes *inicio = d->cauda->prox;
    Atracoes *atual = inicio;

    do {
        if (strcmp(atual->atracao, nome) == 0) {
            // Se for o único nó
            if (atual->prox == atual) {
                free(atual);
                d->cauda = NULL;
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                if (atual == d->cauda) {
                    d->cauda = atual->ant;
                }
                free(atual);
            }
            d->quantidade--;
            printf("Atração \"%s\" removida com sucesso.\n", nome);
            return;
        }
        atual = atual->prox;
    } while (atual != inicio);

    printf("Atração \"%s\" não localizada.\n", nome);
}

// FUNÇÕES DE PERSONALIZAÇÃO

/* Função que faz a aplicação do questionário para o usuário, onde foi realizada a divisão do tipo de atividade nas categorias de natureza, cultural, 
festivo e relaxante. As perguntas são feitas de acordo com as categorias e é acumulado a quantidade de pontos por tipo de atração para montar o roteiro.*/
void aplicarQuestionario(int *natureza, int *cultural, int *festivo, int *relaxante) {
    int resposta;

    printf("Responda com o número da opção escolhida.\n\n");

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

/*A função recebe como parametro o descritor que está associado à lista de atrações e os dados do questionário. A função aplica a pontuação nas atrações que
estão distribuidas de acordo com as categorias definidas. Dessa forma conseguimos priorizar qual atração será feita em que ordem.*/
void aplicarPontuacaoNasAtracoes(Descritor *d, int natureza, int cultural, int festivo, int relaxante) {
    if (d->cauda == NULL) return;

    Atracoes *inicio = d->cauda->prox;
    Atracoes *aux = inicio;
    do {
        switch (aux->categoria) {
            case NATUREZA:
                aux->pontuacao += natureza;
                break;
            case CULTURAL:
                aux->pontuacao += cultural;
                break;
            case FESTIVO:
                aux->pontuacao += festivo;
                break;
            case RELAXANTE:
                aux->pontuacao += relaxante;
                break;
        }
        aux = aux->prox;
    } while (aux != inicio);
}

/*Função que ordena as atrações por pontuação. A ordenação é feita trocando os dados da cidade com maior pontuação pela de menor pontuação, se esta estiver
numa posição superior à ela. */
void ordenarAtracoesPontuacao(Descritor *d) {
    if (d == NULL || d->cauda == NULL) return;

    int trocou;
    Atracoes *atual;
    Atracoes *ultimo = NULL;

    do {
        trocou = 0;
        atual = d->cauda->prox; // Começa do primeiro elemento

        while (atual->prox != d->cauda->prox && atual->prox != ultimo) {
            if (atual->pontuacao < atual->prox->pontuacao) { // Ordena DESCENDENTE
                // Troca os dados mantendo a integridade da lista circular
                Atracoes temp = *atual;
                
                // Troca nome
                strcpy(atual->atracao, atual->prox->atracao);
                strcpy(atual->prox->atracao, temp.atracao);
                
                // Troca outros campos
                atual->categoria = atual->prox->categoria;
                atual->prox->categoria = temp.categoria;
                
                atual->pontuacao = atual->prox->pontuacao;
                atual->prox->pontuacao = temp.pontuacao;
                
                trocou = 1;
            }
            atual = atual->prox;
        }
        ultimo = atual;
    } while (trocou);
}

/*mostra o ranking das atracoes de acordo com a pontuacao*/
void mostrarRanking(Descritor *d) {
    if (d == NULL || d->cauda == NULL) {
        printf("Nenhuma atração cadastrada.\n");
        return;
    }

    printf("\n\t ATRAÇÕES PRIORITÁRIAS \t\n");
    Atracoes *atual = d->cauda->prox;
    int cont = 0;
    
    // Primeiro mostra as com pontuação
    do {
        if (atual->pontuacao > 0) {
            printf("%d. %s\n", ++cont, atual->atracao);
        }
        atual = atual->prox;
    } while (atual != d->cauda->prox);

    printf("\n\t ATRAÇÕES SECUNDÁRIAS \t\n");
    cont = 0;
    atual = d->cauda->prox;
    do {
        if (atual->pontuacao == 0) {
            printf("%d. %s\n", ++cont, atual->atracao);
        }
        atual = atual->prox;
    } while (atual != d->cauda->prox);
}

/*Após a realização do questionário e da organização das atrações de acordo com a pontuação, é feita a impressão do roteiro de acordo com as preferencias do
viajante. Verificamos a quantidade de dias que irá durar a estadia do usuário, com isso conseguimos dividir as atrações pela quantidade de dias em que ele
vai permanecer na cidade. Posteriormente, então, as atrações são atribuidas de acordo com a pontuação do questionário, priorizando as atividades que 
sejam de maior interesse do usuário.*/
void imprimeRoteiroPersonalizado(Cidades *lista, Viagem *viagemProgramada) {
    if (viagemProgramada == NULL) {
        printf("Nenhuma viagem cadastrada.\n");
        return;
    }

    // Cabeçalho da viagem
    printf("ROTEIRO PARA VIAGEM À: %s.\n"
           "DURAÇÃO: %d dias.\n\n",
           viagemProgramada->cidade->cidade,
           viagemProgramada->duracaoEstadia);

    // Localiza a cidade no cadastro
    Cidades *cidadeAtual = lista;
    while (cidadeAtual != NULL) {
        if (strcmp(cidadeAtual->cidade,
                   viagemProgramada->cidade->cidade) == 0) {
            break;
        }
        cidadeAtual = cidadeAtual->prox;
    }
    if (cidadeAtual == NULL) {
        printf("Cidade %s não encontrada no cadastro.\n\n",
               viagemProgramada->cidade->cidade);
        return;
    }

    // Acessa o descritor de atrações
    Descritor *d = cidadeAtual->atracao;
    if (d == NULL || d->cauda == NULL) {
        printf("Nenhuma atração cadastrada para %s.\n\n",
               cidadeAtual->cidade);
        return;
    }

    // Prepara contagem e ponteiros
    int totalAtracoes     = d->quantidade;
    int atracoesRestantes = totalAtracoes;
    int dias              = viagemProgramada->duracaoEstadia;
    int porDia            = totalAtracoes / dias;
    if (porDia == 0) porDia = 1;

    Atracoes *atracaoAtual = d->cauda->prox;
    printf("Roteiro Diário:\n");

    // Imprime roteiro dia a dia
    for (int dia = 1; dia <= dias && atracoesRestantes > 0; dia++) {
        printf("Dia %d:\n", dia);
        for (int i = 0; i < porDia && atracoesRestantes > 0; i++) {
            printf("  - %s | Descrição: %s | Horário: %s\n",
                   atracaoAtual->atracao, atracaoAtual->descricao, atracaoAtual->descricaoHorario);
            atracaoAtual = atracaoAtual->prox;
            atracoesRestantes--;
        }
        printf("\n");
    }
}

//libera a memoria dedicada as cidades e as atracoes
void liberarMemoria(Cidades *listaCidades) {
    Cidades *cidadeAtual = listaCidades;
    
    while (cidadeAtual != NULL) {
        Cidades *cidadeTemp = cidadeAtual;

        if (cidadeAtual->atracao != NULL && cidadeAtual->atracao->cauda != NULL) {
            Atracoes *inicio = cidadeAtual->atracao->cauda->prox;
            Atracoes *atual = inicio;

            do {
                Atracoes *proxima = atual->prox;
                free(atual);
                atual = proxima;
            } while (atual != NULL && atual != inicio);

            free(cidadeAtual->atracao);  // libera o descritor
        }

        cidadeAtual = cidadeAtual->prox;
        free(cidadeTemp);
    }
}
