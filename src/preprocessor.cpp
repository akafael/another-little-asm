/**
 * Pré-Compilador
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "msgs_pt.h"
#include "preprocessor.h"

using namespace std;

int preprocessor(int argc, char ** argv)
{
    // 1 arquivo de entrada .asm;
    // arquivo de saida gerado pelo programa  no formato .pre;
    string arquivo_entrada = argv[2];
    string arquivo_saida   = argv[2];
    arquivo_saida.replace(arquivo_saida.length()-4, arquivo_saida.length(), ".pre");

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
        bool ignoreLine = false;
        char character;

        // Deixa todos caracteres em caixa alta
        std::transform(line.begin(), line.end(),line.begin(), ::toupper);

        // Detecta e Remove Comentários
        character = line.find(';');
        if(character!=std::string::npos){
            line = line.substr(0,character);
        }

       if(!ignoreLine){
           // Escreve linha no arquivo de saída
           ArquivoPRE << line << '\n';
       }
    }

    ArquivoPRE.close();
    ArquivoASM.close();

    return 0;
}
