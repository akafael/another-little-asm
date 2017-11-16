/**
 * Processor Simulator
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "msgs_pt.h"

using namespace std;

typedef struct
{
    int accumulator;
    int programCounter;
} mini_processor;

int simulator(string input_file)
{
    mini_processor mProcessor;
    ifstream fileEXE(input_file.c_str());

    // Teste se ambos o aquivo foi aberto corretamente;
    if (!(fileEXE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    string line;

    // Percorre todas as linhas do arquivo
    for(int lineCount=0;getline(fileEXE,line);lineCount++)
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
