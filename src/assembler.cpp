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

#include "msgs_pt.h"
#include "assembler.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

int assembler(int argc, char * argv[])
{

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
    for(int lineCount = 0 ;getline(ArquivoASM,line);lineCount++)
    {

        vector<token> vtoks;

        ////////////// Análise Léxica ///////////////
        for (int i=0; i<line.length(); ++i){
            // Identifica tokens e pula para o fim do token
            token tok = scanner(line,&i);

            switch (tok.type)
            {
                case ERRCHAR:
                case ERRNUM:
                case INVALID:
                    cerr << PRINT_ERR(arquivo_entrada,lineCount,MSG_ERR_INVALID_TOKEN);
                    break;
                case SPC:
                    // Elimina Espaços em Branco
                    break;
                case
                default:
                    vtoks.push_back(tok);
            }

            //cout << tok.type << ' ' << tok.string << '\n';
        }

        ////////////// Análise Semantica ///////////////
        vector<symbol> vsymbs; ///< Lista de simbolos
        for(vector<token>::iterator it = vtoks.begin(); it != vtoks.end();++it)
        {
            symbol symb;
            int code = -1;

            switch ((*it).type) {
                case COMMA:
                case COLON:
                case PLUS:
                case MINUS:
                case SPC:
                case LINE_END:
                case STR_END:
                    symb.text = (*it).string;
                    symb.type = SYM_TERM;
                    vsymbs.push_back(symb);
                    break;

                case WORD:
                    code = isValidInstruction((*it).string);
                    if(code!=INVALID_INSTRUCTION)
                    {
                        symb.text = (*it).string;
                        symb.type = SYM_INSTRUCTION;
                        vsymbs.push_back(symb);
                    }
                    else{
                        symb.text = (*it).string;
                        symb.type = SYM_LABEL;
                        vsymbs.push_back(symb);
                    }
                    break;

                case NUM_DEC:
                    symb.text = (*it).string;
                    symb.type = SYM_NUM_DEC;
                    vsymbs.push_back(symb);

                case NUM_HEX:
                    symb.text = (*it).string;
                    symb.type = SYM_NUM_HEX;
                    vsymbs.push_back(symb);
            }
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
