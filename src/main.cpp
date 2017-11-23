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
    if (argc< 1)
    {
        cout << MSG_ERR_ARGUMENT_NUMBER;
        return 1;
    }
    else if((argc == 4)&&(argv[1][0]=='-'))
    {
        // 1 arquivo de entrada .pre;
        // arquivo de saida gerado pelo programa  no formato .obj;
        string arquivo_entrada = argv[2];
        string arquivo_saida   = argv[3];

        switch(argv[1][1])
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
    else
    {
        for(int i = 1; i < argc; i++)
        {
            string arquivo_entrada = argv[i];

            // Remove extensão do arquivo
            string basename = arquivo_entrada;
            int charPosition = basename.rfind('.');
            if(charPosition != std::string::npos)
            {
                // Caso achou a string
                basename = basename.substr(0,charPosition);
            }

            string file_preprocessor = basename+".pre";
            string file_macroeval = basename+".mcr";
            string file_assembler = basename+".o";

            cout << arquivo_entrada << endl;

            // Executa verificações em sequencia e para em caso de erro
            if((preprocessor(arquivo_entrada,file_preprocessor))||
            (macroeval(file_preprocessor,file_macroeval))||
            (assembler(file_macroeval,file_assembler)))
            {
                cout << arquivo_entrada << ":" << MSG_ERR_ASSEMBLY;
            }
        }
    }

    return 0;
}
