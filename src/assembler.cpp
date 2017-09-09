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

        vector<token> vtoks;   ///< Tabela de Tokens
        vector<symbol> vsymbs; ///< Tabela de Token

        ////////////// Análise Léxica ///////////////
        for (int i=0; i<line.length(); ++i){
            // Identifica tokens e pula para o fim do token
            token tok = scanner(line,&i);

            switch (tok.type)
            {
                case ERRCHAR:
                case ERRNUM:
                case INVALID:
                    cerr << PRINT_ERR_TOKEN(arquivo_entrada,lineCount,tok.string);
                    break;
                case SPC:
                    // Elimina Espaços em Branco
                    break;
                default:
                    vtoks.push_back(tok);
            }

            #if DEBUG_LEXER
                cout << tok.type << '\t' << tok.string << endl;
            #endif
        }

        ////////////// Análise Semantica ///////////////

        instruction inst;
        label lbl;
        // Arvores de Derivação basedos na quantidade de argumentos

        if(vtoks.size()==0)
        {
            // Ignora Linha em Branco
        }
        else if((vtoks.size()==1)&&(vtoks[0].type==WORD))
        {
            // INST0
        }
        else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD))
        {
            // INST1
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)\
                &&(vtoks[2].type==COMMA)&&(vtoks[3].type==WORD))
        {
            // INST 2
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON))
        {
            // Label
        }
        else if((vtoks.size()==3)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD))
        {
            // Label + INST0
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD))
        {
            // Label + INST1
        }
        else if((vtoks.size()==6)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD)&&(vtoks[4].type==COMMA)\
                &&(vtoks[5].type==WORD))
        {
            // Label + INST2
        }
        else
        {
            // Instrução Mal formatada
            cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            for(vector<token>::iterator it = vtoks.begin(); it != vtoks.end();++it)
            {
                cout << (*it).type << '\t';
            }
            cout << endl;
        }

        // Escrita no Arquivo
        //ArquivoPRE << tok.type << ' ';

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
