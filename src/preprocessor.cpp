/**
 * Pré-Compilador
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "msgs_pt.h"
#include "preprocessor.h"
#include "lexer.h"

using namespace std;

int preprocessor(int argc, char ** argv)
{
    // 1 arquivo de entrada .asm;
    // arquivo de saida gerado pelo programa  no formato .pre;
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
    bool errorDetected = false;

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

        // Detecta EQU e verifica sintaxe
        character = line.find("EQU");
        if(character!=std::string::npos){

            vector<token> vtoks = tokenizer(line);

            if(!((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
               &&(vtoks[2].type==WORD)&&((vtoks[3].type==NUM_DEC||vtoks[3].type==WORD))))
            {
                // Uso Incorreto do EQU
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }

        // Detecta IF e verifica sintaxe
        character = line.find("IF");
        if(character!=std::string::npos){

            vector<token> vtoks = tokenizer(line);

            if(!((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)))
            {
                // Uso Incorreto do IF
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }

       if(!ignoreLine){
           // Escreve linha no arquivo de saída
           ArquivoPRE << line << '\n';
       }
    }

    ArquivoPRE.close();
    ArquivoASM.close();

    if(errorDetected){
        // Gera código de erro
        return 1;
    }else{
        return 0;
    }
}
