#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int natureza = 0, cultural = 0, festivo = 0, relaxante = 0;
    Cidades* listaCidades = NULL;

    // carrega os dados das cidades e atrações
    carregarDados(&listaCidades);

    listarCidades(listaCidades);

    char nomeCidade[30];
    printf("Digite o nome da cidade para qual deseja programar a viagem:\n");
    
    // questionario para experiencia personalizada
    aplicarQuestionario(&natureza, &cultural, &festivo, &relaxante);
    
    // aplica pontuação nas atrações de cada cidade
    Cidades* cidadeAtual = listaCidades;
    while (cidadeAtual != NULL) {
        aplicarPontuacaoNasAtracoes(cidadeAtual->atracao, natureza, cultural, festivo, relaxante);
        cidadeAtual = cidadeAtual->prox;
    }
    listarCidadesComAtracoes(listaCidades);
    return 0;
}
