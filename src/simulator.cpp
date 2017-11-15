/**
 * Processor Simulator
 *
 */

#include <iostream>
#include <string>

#include "msgs_pt.h"

int simulator(string input_file)
{
    ifstream fileEXE(input_file.c_str());

    // Teste se ambos o aquivo foi aberto corretamente;
    if (!(fileEXE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    string line;

    // Percorre todas as linhas do arquivo
    for(int lineCount=0;getline(ArquivoASM,line);lineCount++)
    {
        char charPosition = 0;
        /// @todo Identificar Segmento de texto e gerar vetor para leitura
        charPosition = line.find("T: ");
        if(charPosition != std::string::npos)
        {
            /// @todo definir um vetor de números a partir da leitura de texto
        }
    }
}
