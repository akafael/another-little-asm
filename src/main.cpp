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
#include "macroeval.h"

int main(int argc, char** argv){

    // Verifica Formatação dos Argumentos
    char *operacao = argv[1];
    if (argc< 2 || operacao[0] != '-' || strlen(operacao) != 2)
    {
        printf(MSG_ERR_INVALID_ARGUMENT);
        return 1;
    }
    else if (argc != 4)
    {
        printf(MSG_ERR_ARGUMENT_NUMBER);
        return 1;
    }

    switch(operacao[1])
    {
    case 'p':
        /// Pré Processamento (EQU, IF)
        return preprocessor(argc,argv);

    case 'm':
        /// Avaliação das Macros
        return macroeval(argc,argv);

    case 'o':
        /// Montador
        return assembler(argc,argv);

    default:
        printf(MSG_ERR_INVALID_ARGUMENT);
        return 1;
    }

    return 0;
}
