#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int natureza = 0, cultural = 0, festivo = 0, relaxante = 0;
    Viagem* viagemProgramada = NULL;
    Cidades* listaCidades = criaListaVazia();

    // carrega os dados das cidades e atrações
    carregarDados(&listaCidades);
    int opcao;
    int opcaoAdmin;

    do {
        printf("\n----------------------- MENU PRINCIPAL -----------------------\n");
        printf("1 - Ver destinos com atrações\n");
        printf("2 - Programar viagem\n");
        printf("3 - Acesso administrativo\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarCidadesComAtracoes(listaCidades);
                break;
            
            case 2:
                printf("\n=== CIDADES DISPONÍVEIS ===\n");
                listarCidades(listaCidades);
                char nomeCidade[30];
                int duracao;
                
                printf("Qual o nome da cidade para qual deseja programar a viagem:\n");
                while (getchar() != '\n'); 
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                
                printf("Qual a duração da sua estadia em dias?\n");
                scanf("%d", &duracao);

                viagemProgramada = (Viagem *)malloc(sizeof(Viagem));
                if (viagemProgramada == NULL) {
                    printf("Erro ao alocar memória para a viagem!\n");
                    break;
                }
                Cidades *cidadeSelecionada = buscarCidade(listaCidades, nomeCidade);
                if (cidadeSelecionada == NULL) {
                    printf("Cidade não encontrada!\n");
                    break;
                }
                definirViagem(viagemProgramada, cidadeSelecionada, duracao);
                
                // questionario para experiencia personalizada
                printf("\nPara garantir uma experiência única, responda o questionário a seguir:\n");
                printf("Com ele montaremos um roteiro de viagem exclusivo para você, de acordo com suas preferências pessoais.");
                aplicarQuestionario(&natureza, &cultural, &festivo, &relaxante);
                
                printf("Prontinho! Agora já temos organizada uma viagem inesquecível para você!\n O que deseja fazer?\n");
                
                // aplica pontuação nas atrações de cada cidade
                Cidades* cidadeAtual = listaCidades;
                while (cidadeAtual != NULL && strcmp(cidadeAtual->cidade, nomeCidade) != 0) {
                        cidadeAtual = cidadeAtual->prox;
                }
                
                if (cidadeAtual == NULL) {
                    printf("Cidade não encontrada!\n");
                    break;
                }
                aplicarPontuacaoNasAtracoes(cidadeAtual->atracao, natureza, cultural, festivo, relaxante);
                ordenarAtracoesPontuacao(cidadeAtual->atracao);
                int opcaoRoteiro;
                do {
                    printf("\n1 - Ver ranking de prioridades\n");
                    printf("2 - Roteiro personalizado\n");
                    printf("3 - Ver outras cidades\n");
                    printf("Escolha: ");
                    scanf("%d", &opcaoRoteiro);

                    switch (opcaoRoteiro) {
                        case 1:
                            mostrarRanking(cidadeAtual->atracao);
                            break;
                        case 2:
                            imprimeRoteiroPersonalizado(cidadeAtual, viagemProgramada);
                            break;
                        case 3:
                            listarCidades(listaCidades);
                            
                            break;
                    }
                } while (opcaoRoteiro != 3);
                break;
            
            case 3:
                menuAdministrativo(&listaCidades);
                break;
            case 4:
                printf("Saindo da aplicação...\n");
                liberarMemoria(listaCidades);
                return 0;
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while (opcao != 5);

    liberarMemoria(listaCidades);

    return 0;
}
