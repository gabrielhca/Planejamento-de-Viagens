#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int natureza = 0, cultural = 0, festivo = 0, relaxante = 0;
    Viagem* viagemProgramada = NULL;
    Cidades* listaCidades = criaListaVazia();

    if(listaCidades == NULL){
        printf("Erro ao alocar memória para as cidades!\n");
        return 1;
    }

    // carrega os dados das cidades e atrações
    carregarDados(&listaCidades);
    int opcao;

    do {
        printf ("\n------------ O QUE DESEJA FAZER? ------------\n");
        printf ("\n1 - Verificar destinos de viagens.\n");
        printf ("\n2 - Verificar destinos de viagens e atrações disponíveis.\n");
        printf ("\n3 - Programar viagem.\n");
        printf ("\n4 - Sair\n");
        printf ("\nEscolha uma opção:\n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                listarCidades(listaCidades);
                break;
            
            case 2:
                listarCidadesComAtracoes(listaCidades);
                break;
            
            case 3:
                char nomeCidade[30];
                int duracao;
                
                printf("Qual o nome da cidade para qual deseja programar a viagem:\n");
                while (getchar() != '\n'); 
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                
                printf("Qual a duração da sua estadia em dias?\n");
                scanf("%d", &duracao);
                
                viagemProgramada = definirViagem(nomeCidade, duracao);
                
                // questionario para experiencia personalizada
                aplicarQuestionario(&natureza, &cultural, &festivo, &relaxante);
                
                // aplica pontuação nas atrações de cada cidade
                Cidades* cidadeAtual = listaCidades;
                while (cidadeAtual != NULL && strcmp(cidadeAtual->nome, nomeCidade) != 0) {
                        cidadeAtual = cidadeAtual->prox;
                }
                
                if (cidadeAtual == NULL) {
                    printf("Cidade não encontrada!\n");
                    break;
                }
                aplicarPontuacaoNasAtracoes(cidadeAtual->atracao, natureza, cultural, festivo, relaxante);
                imprimeRoteiroPersonalizado(cidadeAtual, viagemProgramada);
                break;
            
            case 4:
                printf("Encerrando a aplicação.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while (opcao != 4);

    void liberarMemoria(listaCidades);

    return 0;
}
