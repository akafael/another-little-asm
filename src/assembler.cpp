/**
 * Montador
 *
 * @authors Rafael Lima e João Pedro Franch
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
    int currentSymbolAddr = 0;

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
                    cerr << PRINT_ERR_TOKEN(lineCount,tok.string);
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

        vector<symbol> symbolsTable;
        vector<label> labelsTable;

        // Arvores de Derivação
        if(vtoks.size()==0)
        {
            // Ignora Linha em Branco
        }
        else if((vtoks.size()==1)&&(vtoks[0].type==WORD))
        {
            // INST0
            int code = isValidInstructionCall(vtoks[0].string);
            if(code!=INVALID_INSTRUCTION)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb;
                tmp_symb.type = SYM_INSTRUCTION;
                tmp_symb.content = code;
                tmp_symb.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr++;
            }
            else
            {
                // Possível Erro: "Label Mal Formatado" ou "Instrução Inválida"
                cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD))
        {
            // INST1
            int code = isValidInstructionCall(vtoks[0].string,vtoks[1].string);
            if(code!=INVALID_INSTRUCTION)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0,tmp_symb1;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                /// @todo Pesquisar Labels na labelTable e pegar endereço
                tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                tmp_symb1.address = currentSymbolAddr+1;
                symbolsTable.push_back(tmp_symb1);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=2;
            }
            else
            {
                // Possível Erro: "Label Mal Formatado" ou "Instrução Inválida"
                cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)\
                &&(vtoks[2].type==COMMA)&&(vtoks[3].type==WORD))
        {
            // INST 2
            int code = isValidInstructionCall(vtoks[0].string,vtoks[1].string,vtoks[3].string);
            if(code!=INVALID_INSTRUCTION)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0,tmp_symb1,tmp_symb2;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                /// @todo Pesquisar Labels na labelTable e pegar endereço
                tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                tmp_symb1.address = currentSymbolAddr+1;
                symbolsTable.push_back(tmp_symb1);

                tmp_symb2.type = SYM_LABEL;
                /// @todo Pesquisar Labels na labelTable e pegar endereço
                tmp_symb2.content = UNDEFINED_LABEL_ADDR;
                tmp_symb2.address = currentSymbolAddr+2;
                symbolsTable.push_back(tmp_symb2);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=3;
            }
            else
            {
                // Possível Erro: "Instrução Inválida", "Argumento Inválido"
                cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON))
        {
            // Label
        }
        else if((vtoks.size()==3)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD))
        {
            // Label + INST0

            // INST0
            int code = isValidInstructionCall(vtoks[2].string);
            if(code!=INVALID_INSTRUCTION)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb;
                tmp_symb.type = SYM_INSTRUCTION;
                tmp_symb.content = code;
                tmp_symb.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr++;
            }
            else
            {
                // Possível Erro: "Label Mal Formatado" ou "Instrução Inválida"
                cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD))
        {
            // Label + INST1

            // INST1
            int code = isValidInstructionCall(vtoks[2].string,vtoks[3].string);
            if(code!=INVALID_INSTRUCTION)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0,tmp_symb1;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                /// @todo Pesquisar Labels na labelTable e pegar endereço
                tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                tmp_symb1.address = currentSymbolAddr+1;
                symbolsTable.push_back(tmp_symb1);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=2;
            }
            else
            {
                // Possível Erro: "Label Mal Formatado" ou "Instrução Inválida"
                cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else if((vtoks.size()==6)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD)&&(vtoks[4].type==COMMA)\
                &&(vtoks[5].type==WORD))
        {
            // Label + INST2

            // INST 2
            int code = isValidInstructionCall(vtoks[2].string,vtoks[3].string,vtoks[5].string);
            if(code!=INVALID_INSTRUCTION)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0,tmp_symb1,tmp_symb2;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                /// @todo Pesquisar Labels na labelTable e pegar endereço
                tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                tmp_symb1.address = currentSymbolAddr+1;
                symbolsTable.push_back(tmp_symb1);

                tmp_symb2.type = SYM_LABEL;
                /// @todo Pesquisar Labels na labelTable e pegar endereço
                tmp_symb2.content = UNDEFINED_LABEL_ADDR;
                tmp_symb2.address = currentSymbolAddr+2;
                symbolsTable.push_back(tmp_symb2);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=3;
            }
            else
            {
                // Possível Erro: "Instrução Inválida", "Argumento Inválido"
                cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else
        {
            // Instrução Mal formatada
            cerr<<PRINT_ERR_INSTRUCTION(lineCount,line);

            #if DEBUG_ASSEMBLER
            for(vector<token>::iterator it = vtoks.begin(); it != vtoks.end();++it)
            {
                cout << (*it).type << '\t';
            }
            cout << endl;
            #endif
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
