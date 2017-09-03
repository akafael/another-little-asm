/**
 * Montador
 *
 * @author Rafael e Willian
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>

#include "assembler.h"
#include "lexer.h"
#include "msgs_pt.h"

using namespace std;

int assembler(int argc, char * argv[]){

    // 1 arquivo de entrada .pre;
    // arquivo de saida gerado pelo programa  no formato .obj;
    string arquivo_entrada = argv[2];
    string arquivo_saida   = argv[2];
    arquivo_saida.replace(arquivo_saida.length()-4, arquivo_saida.length(), ".obj");

    ifstream ArquivoASM(arquivo_entrada.c_str()); // input;
    ofstream ArquivoPRE(arquivo_saida.c_str()); // output;

    // Teste se ambos os aquivos foram abertos corretamente;
    if (!(ArquivoASM.is_open() && ArquivoPRE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    string line;
    for(int lineCount = 0 ;getline(ArquivoASM,line);lineCount++){

        vector<token> vtoks;

        ////////////// Análise Léxica ///////////////
        for (int i=0; i<line.length(); ++i){
            // Identifica tokes e pula para o fim do token
            token tok = scanner(line,&i);

            // Elimina Espaços em Branco e Armazena Tokens Válidos
            if ((tok.type != SPC))
                vtoks.push_back(tok);

            cout << tok.type << ' ';
        }

        // Escrita no Arquivo
        //ArquivoPRE << tok.type << ' ';

    }

    ArquivoPRE.close();
    ArquivoASM.close();

    return 0;
 }
