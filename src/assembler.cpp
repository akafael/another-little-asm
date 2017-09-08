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
    for(int lineCount = 0 ;getline(ArquivoASM,line);lineCount++){

        vector<token> vtoks;

        ////////////// Análise Léxica ///////////////
        for (int i=0; i<line.length(); ++i){
            // Identifica tokes e pula para o fim do token
            token tok = scanner(line,&i);

            switch (tok.type) {
                case ERRCHAR:
                case ERRNUM:
                case INVALID:
                    cerr << PRINT_ERR(arquivo_entrada,lineCount,MSG_ERR_INVALID_TOKEN);
                    break;
                case SPC:
                    // Elimina Espaços em Branco
                    break;
                default:
                    vtoks.push_back(tok);
            }

            //cout << tok.type << ' ' << tok.string << '\n';
        }

        // Escrita no Arquivo
        //ArquivoPRE << tok.type << ' ';

    }

    ArquivoPRE.close();
    ArquivoASM.close();

    if(errorDetected){
        return 1;
    }else{
        return 0;
    }
 }
