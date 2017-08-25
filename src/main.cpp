/**
 * Trabalho 1 - Software Básico
 *
 * @authors Rafael Lima e João Pedro Franch
 * @version 0.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "mensagens.h"
#include "preprocessador.h"
#include "montador.h"

int main(int argc, char** argv){

    // Verifica Formatação dos Argumentos
    char *operacao = argv[1];
    if (argc< 2 || operacao[0] != '-' || strlen(operacao) != 2){
        printf(MSG_ERRO_SEGUNDO_ARGUMENTO);
        return 2;
    }

    char op = operacao[1];
    switch(op)
    {

    case 'p':
        /// Pré Processamento (EQU, IF)

        // Verifica Quantidade de Argumentos
        if (argc != 3){
            printf(MSG_ERRO_ARGUMENTOS);
            return 1;
        }
        preProcessador(argc,argv);
        break;

     // Montador
    case 'o':
        // Verifica Quantidade de Argumentos
        if (argc != 4){
            printf(MSG_ERRO_ARGUMENTOS);
            return 1;
        }
        montador(argc,argv);
        printf(MSG_ERRO);
        break;

    default:
        printf(MSG_ERRO_SEGUNDO_ARGUMENTO);
        return 1;
    }

    return 0;
}
