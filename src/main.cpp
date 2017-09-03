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

#include "msgs_pt.h"
#include "preprocessor.h"
#include "assembler.h"

int main(int argc, char** argv){

    // Verifica Formatação dos Argumentos
    char *operacao = argv[1];
    if (argc< 2 || operacao[0] != '-' || strlen(operacao) != 2){
        printf(MSG_ERR_INVALID_ARGUMENT);
        return 2;
    }

    char op = operacao[1];
    switch(op)
    {

    case 'p':
        /// Pré Processamento (EQU, IF)

        // Verifica Quantidade de Argumentos
        if (argc != 3){
            printf(MSG_ERR_ARGUMENT_NUMBER);
            return 1;
        }
        preprocessor(argc,argv);
        break;

     // Montador
    case 'o':
        // Verifica Quantidade de Argumentos
        if (argc != 3){
            printf(MSG_ERR_ARGUMENT_NUMBER);
            return 1;
        }
        assembler(argc,argv);
        break;

    default:
        printf(MSG_ERR_INVALID_ARGUMENT);
        return 1;
    }

    return 0;
}
