#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"



int main (){

    int natureza = 0, cultural = 0, festivo = 0, relaxante = 0;

    // questionario para experiencia personalizada
    aplicarQuestionario(&natureza, &cultural, &festivo, &relaxante);
    
    // classifica as atrações de acordo com o gosto pessoal do usuario
    aplicarPontuacaoNasAtracoes(atracoesInicio, natureza, cultural, festivo, relaxante);

    return 0;
}