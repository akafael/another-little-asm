/**
 * Trabalho 1 - Software Básico
 *
 * @authors Rafael Lima e João Pedro Franch
 * @version 0.2
 */

#include <iostream>
#include <string.h>

#include "msgs_pt.h"
#include "preprocessor.h"
#include "assembler.h"
#include "macroeval.h"

using namespace std;

int main(int argc, char** argv){

    // Verifica Formatação dos Argumentos
    char *operacao = argv[1];
    if (argc< 2 || operacao[0] != '-' || strlen(operacao) != 2)
    {
        cout << MSG_ERR_INVALID_ARGUMENT;
        return 1;
    }
    else if (argc != 4)
    {
        cout << MSG_ERR_ARGUMENT_NUMBER;
        return 1;
    }
    else
    {
        // 1 arquivo de entrada .pre;
        // arquivo de saida gerado pelo programa  no formato .obj;
        string arquivo_entrada = argv[2];
        string arquivo_saida   = argv[3];

        switch(operacao[1])
        {
        case 'p':
            /// Pré Processamento (EQU, IF)
            return preprocessor(arquivo_entrada,arquivo_saida);

        case 'm':
            /// Avaliação das Macros
            return macroeval(arquivo_entrada,arquivo_saida);

        case 'o':
            /// Montador
            return assembler(arquivo_entrada,arquivo_saida);

        default:
            cout << MSG_ERR_INVALID_ARGUMENT;
            return 1;
        }
    }

    return 0;
}
