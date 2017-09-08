/**
 * Pré-Compilador
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "msgs_pt.h"
#include "macroeval.h"

using namespace std;

int macroeval(int argc, char ** argv)
{
    // 1 arquivo de entrada .pre;
    // arquivo de saida gerado pelo programa  no formato .mcr;
    string arquivo_entrada = argv[2];
    string arquivo_saida   = argv[3];

    ifstream ArquivoASM(arquivo_entrada.c_str()); // input;
    ofstream ArquivoPRE(arquivo_saida.c_str()); // output;

    // Teste se ambos os aquivos foram abertos corretamente;
    if (!(ArquivoASM.is_open() && ArquivoPRE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    string line;

    // Percorre todas as linhas do arquivo
    for(int lineCount=0;getline(ArquivoASM,line);lineCount++)
    {
       /// @todo Fazer validação das macros, IF e EQV
       // Escreve linha no arquivo de saída
       ArquivoPRE << line << '\n';
    }

    ArquivoPRE.close();
    ArquivoASM.close();

    return 0;
}
