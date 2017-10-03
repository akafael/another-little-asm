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

#include "msgs_pt.h"
#include "assembler.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

bool lexicalAnalysisInstruction(int lineCount,string line,vector<token> vtoks,vector<symbol> *symbolsTb,vector<label> *labelsTb, int *currentSymbAd);

int assembler(int argc, char * argv[])
{

    // 1 arquivo de entrada .pre;
    // arquivo de saida gerado pelo programa  no formato .obj;
    string arquivo_entrada = argv[2];
    string arquivo_saida   = argv[3];

    ifstream InputFILE(arquivo_entrada.c_str()); // input;
    ofstream OutputFILE(arquivo_saida.c_str()); // output;

    // Teste se ambos os aquivos foram abertos corretamente;
    if (!(InputFILE.is_open() && OutputFILE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    vector<symbol> symbolsTable;
    vector<label> labelsTable;

    string line;
    bool errorDetected = false;
    bool isSectionTextDeclared = false;
    bool isSectionDataDeclared = false;
    SectionMode currentSection = SECTION_NONE;
    int currentSymbolAddr = 1;

    for(int lineCount = 0 ;getline(InputFILE,line);lineCount++)
    {

        vector<token> vtoks;   ///< Tabela de Tokens

        ////////////// Análise Léxica ///////////////
        for (int i=0; i<line.length(); ++i){
            // Identifica tokens e pula para o fim do token
            token tok = scanner(line,&i);

            switch (tok.type)
            {
                case ERRCHAR:
                case ERRNUM:
                case INVALID:
                    PRINT_ERR_TOKEN(lineCount,tok.string);
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

        // Arvores de Derivação
        if(vtoks.size()==0)
        {
            // Ignora Linha em Branco
        }
        else if((vtoks.size()==1)&&(vtoks[0].type==WORD))
        {
            // INST0
            int code = isValidInstructionCall(vtoks[0].string);
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else // Instrução Chamada de Instrução Válida
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
        }
        else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD))
        {
            // INST1
            int code = isValidInstructionCall(vtoks[0].string,vtoks[1].string);
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else if(code==INVALID_ARG_NUMBER)
            {
                PRINT_ERR_ARG_NUM(lineCount,line);
            }
            else if(code==INVALID_ARG1)
            {
                PRINT_ERR_ARG(lineCount,line,vtoks[1].string);
            }
            else if(code<=14)// Chamada Válida de instrução
            {
                // Cria Simbolos e coloca na tabela
                symbol tmp_symb0,tmp_symb1;
                int labelPos;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                tmp_symb1.address = currentSymbolAddr+1;

                labelPos = findLabel(labelsTable,vtoks[1].string);
                if(labelPos==LABEL_NOT_FOUND)
                {
                    tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                    tmp_symb1.text = vtoks[1].string;
                    /// @todo Modificar para permitir completar tabela ao final da passagem

                }
                else
                {
                    tmp_symb1.content = labelsTable[labelPos].addr;
                }

                symbolsTable.push_back(tmp_symb1);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=2;
            }
            else
            {
                // Possível Diretiva
                switch (code) {
                    case SECTION:
                        if(vtoks[1].string=="TEXT")
                        {
                            isSectionTextDeclared = true;
                            currentSection = SECTION_TEXT;
                        }
                        else if(vtoks[1].string=="DATA")
                        {
                            isSectionDataDeclared = true;
                            currentSection = SECTION_DATA;
                        }
                        else
                        {// Erro SECTION
                            PRINT_ERR_INVALID_SECTION(lineCount,line);
                        }
                        break;
                    case SPACE0:
                    {
                        int spaceAmount = atoi(vtoks[1].string.c_str());
                        for(int i=0;i<spaceAmount;i++)
                        {
                            symbol tmp_symb0;

                            tmp_symb0.type = SYM_NUM_DEC;
                            tmp_symb0.content = 0;
                            tmp_symb0.address = currentSymbolAddr+i;
                            symbolsTable.push_back(tmp_symb0);
                        }
                        currentSymbolAddr+=spaceAmount; // Atualiza Endereços
                        break;
                    }
                    case CONST:
                        // Erro
                        PRINT_ERR_ARG(lineCount,line,vtoks[1].string);
                        break;
                }
            }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)\
              &&(vtoks[2].type==PLUS)&&(vtoks[3].type==NUM_DEC))
        {
          int code = isValidInstructionCall(vtoks[0].string,vtoks[1].string);
          if(code==INVALID_INSTRUCTION)
          {
              PRINT_ERR_INSTRUCTION(lineCount,line);
          }
          else if(code==INVALID_ARG_NUMBER)
          {
              PRINT_ERR_ARG_NUM(lineCount,line);
          }
          else if(code==INVALID_ARG1)
          {
              PRINT_ERR_ARG(lineCount,line,vtoks[1].string);
          }
          else if(code<=14)// Chamada Válida de instrução
          {
              // Cria Simbolos e coloca na tabela
              symbol tmp_symb0,tmp_symb1;
              int labelPos;

              tmp_symb0.type = SYM_INSTRUCTION;
              tmp_symb0.content = code;
              tmp_symb0.address = currentSymbolAddr;
              symbolsTable.push_back(tmp_symb0);

              tmp_symb1.type = SYM_LABEL;
              tmp_symb1.address = currentSymbolAddr+1;

              labelPos = findLabel(labelsTable,vtoks[1].string);
              int numplus=std::atoi(vtoks[3].string.c_str());
              if(labelPos==LABEL_NOT_FOUND)
              {
                  tmp_symb1.content = -1-numplus; //Armazena como negativo para recuperar o numero depois
                  tmp_symb1.text = vtoks[1].string;
                  /// @todo Modificar para permitir completar tabela ao final da passagem

              }
              else
              {
                  tmp_symb1.content = labelsTable[labelPos].addr+numplus;
              }

              symbolsTable.push_back(tmp_symb1);

               // Atualiza Endereço p/ próximo simbolo
              currentSymbolAddr+=2;
          }
          else
          {
            PRINT_ERR_INSTRUCTION(lineCount, line);
          }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)\
                &&(vtoks[2].type==COMMA)&&(vtoks[3].type==WORD))
        {
            // INST 2
            int code = isValidInstructionCall(vtoks[0].string,vtoks[1].string,vtoks[3].string);
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else if(code==INVALID_ARG_NUMBER)
            {
                PRINT_ERR_ARG_NUM(lineCount,line);
            }
            else if(code==INVALID_ARG1)
            {
                PRINT_ERR_ARG(lineCount,line,vtoks[1].string);
            }
            else if(code==INVALID_ARG2)
            {
                PRINT_ERR_ARG(lineCount,line,vtoks[3].string);
            }
            else // Instrução Chamada de Instrução Válida
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0,tmp_symb1,tmp_symb2;
                int labelPos;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                tmp_symb1.address = currentSymbolAddr+1;

                labelPos = findLabel(labelsTable,vtoks[1].string);
                if(labelPos==LABEL_NOT_FOUND)
                {
                    tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                    tmp_symb1.text = vtoks[1].string;
                    /// @todo Modificar para permitir completar tabela ao final da passagem
                }
                else
                {
                    tmp_symb1.content = labelsTable[labelPos].addr;
                }

                symbolsTable.push_back(tmp_symb1);

                tmp_symb2.type = SYM_LABEL;

                labelPos = findLabel(labelsTable,vtoks[3].string);
                if(labelPos==LABEL_NOT_FOUND)
                {
                    tmp_symb2.content = UNDEFINED_LABEL_ADDR;
                    tmp_symb2.text = vtoks[3].string;
                    /// @todo Modificar para permitir completar tabela ao final da passagem
                }
                else
                {
                    tmp_symb2.content = labelsTable[labelPos].addr;
                }
                tmp_symb2.address = currentSymbolAddr+2;
                symbolsTable.push_back(tmp_symb2);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=3;
            }
        }
        else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON))
        {
            // Label
            int labelPos = findLabel(labelsTable,vtoks[0].string);
            if(labelPos==LABEL_NOT_FOUND)
            {
                // Insere Label na tabela de labels
                label tmp_label;
                tmp_label.text = vtoks[0].string;
                /// @bug começando contagem a partir do 1 ao invés do 0
                tmp_label.addr = currentSymbolAddr;

                labelsTable.push_back(tmp_label);
            }
            else
            {
                PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
            }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[4].type==WORD)&&(vtoks[3].type==COLON))
        {
            // Erro Label
            PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
        }
        else if((vtoks.size()==3)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD))
        {
            // Label + INST0
            int labelPos = findLabel(labelsTable,vtoks[0].string);
            if(labelPos==LABEL_NOT_FOUND)
            {
                // Insere Label na tabela de labels
                label tmp_label;
                tmp_label.text = vtoks[0].string;
                tmp_label.addr = currentSymbolAddr;

                labelsTable.push_back(tmp_label);
            }
            else
            {
                PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
            }

            // INST0
            int code = isValidInstructionCall(vtoks[2].string);
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else if(code==INVALID_ARG_NUMBER)
            {
                PRINT_ERR_ARG_NUM(lineCount,line);
            }
            else if(code==SPACE0)
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0;

                tmp_symb0.type = SYM_NUM_DEC;
                tmp_symb0.content = 0;
                tmp_symb0.address = currentSymbolAddr+1;
                symbolsTable.push_back(tmp_symb0);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr++;
            }
            else if(isValidInstructionCall(vtoks[0].string)>0)
            {
                // Erro Uso de palavra chave como Rótulo
                PRINT_ERR_LABEL(lineCount,line);
            }
            else // Instrução Chamada de Instrução Válida
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
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD))
        {
            // Label + INST1
            int labelPos = findLabel(labelsTable,vtoks[0].string);
            if(labelPos==LABEL_NOT_FOUND)
            {
                // Insere Label na tabela de labels
                label tmp_label;
                tmp_label.text = vtoks[0].string;
                tmp_label.addr = currentSymbolAddr;

                labelsTable.push_back(tmp_label);
            }
            else
            {
                PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
            }

            // INST1
            int code = isValidInstructionCall(vtoks[2].string,vtoks[3].string);
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else if(code==INVALID_ARG_NUMBER)
            {
                PRINT_ERR_ARG_NUM(lineCount,line);
            }
            else if(code==INVALID_ARG1)
            {
                PRINT_ERR_ARG(lineCount,line,vtoks[3].string);
            }
            else if(isValidInstructionCall(vtoks[0].string)>0)
            {
               // Erro Uso de palavra chave como Rótulo
               PRINT_ERR_LABEL(lineCount,line);
            }
            else // Instrução Chamada de Instrução Válida
            {
                // Cria Simbolos e coloca na tabela
                symbol tmp_symb0,tmp_symb1;
                int labelPos;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                tmp_symb1.address = currentSymbolAddr+1;

                labelPos = findLabel(labelsTable,vtoks[3].string);
                if(labelPos==LABEL_NOT_FOUND)
                {
                    tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                    tmp_symb1.text = vtoks[3].string;
                    /// @todo Modificar para permitir completar tabela ao final da passagem
                }
                else
                {
                    tmp_symb1.content = labelsTable[labelPos].addr;
                }

                symbolsTable.push_back(tmp_symb1);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=2;
            }
        }
        else if((vtoks.size()==6)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD)&&(vtoks[4].type==COMMA)\
                &&(vtoks[5].type==WORD))
        {
            // Label + INST2
            int labelPos = findLabel(labelsTable,vtoks[0].string);
            if(labelPos==LABEL_NOT_FOUND)
            {
                // Insere Label na tabela de labels
                label tmp_label;
                tmp_label.text = vtoks[0].string;
                tmp_label.addr = currentSymbolAddr;

                labelsTable.push_back(tmp_label);
            }
            else
            {
                PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
            }

            // INST 2
            int code = isValidInstructionCall(vtoks[2].string,vtoks[3].string,vtoks[5].string);
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else if(code==INVALID_ARG_NUMBER)
            {
                PRINT_ERR_ARG_NUM(lineCount,line);
            }
            else if(code==INVALID_ARG1)
            {
                PRINT_ERR_ARG(lineCount,line,vtoks[3].string);
            }
            else if(code==INVALID_ARG2)
            {
                PRINT_ERR_ARG(lineCount,line,vtoks[5].string);
            }
            else if(isValidInstructionCall(vtoks[0].string)>0)
            {
                // Erro Uso de palavra chave como Rótulo
                PRINT_ERR_LABEL(lineCount,line);
            }
            else // Instrução Chamada de Instrução Válida
            {
                // Cria Simbolo e coloca na tabela
                symbol tmp_symb0,tmp_symb1,tmp_symb2;
                int labelPos;

                tmp_symb0.type = SYM_INSTRUCTION;
                tmp_symb0.content = code;
                tmp_symb0.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb0);

                tmp_symb1.type = SYM_LABEL;
                tmp_symb1.address = currentSymbolAddr+1;

                labelPos = findLabel(labelsTable,vtoks[3].string);
                if(labelPos==LABEL_NOT_FOUND)
                {
                    tmp_symb1.content = UNDEFINED_LABEL_ADDR;
                    tmp_symb1.text = vtoks[3].string;
                    /// @todo Modificar para permitir completar tabela ao final da passagem
                }
                else
                {
                    tmp_symb1.content = labelsTable[labelPos].addr;
                }

                symbolsTable.push_back(tmp_symb1);

                tmp_symb2.type = SYM_LABEL;
                tmp_symb2.address = currentSymbolAddr+2;

                labelPos = findLabel(labelsTable,vtoks[5].string);
                if(labelPos==LABEL_NOT_FOUND)
                {
                    tmp_symb2.content = UNDEFINED_LABEL_ADDR;
                    tmp_symb2.text = vtoks[5].string;
                    /// @todo Modificar para permitir completar tabela ao final da passagem
                }
                else
                {
                    tmp_symb2.content = labelsTable[labelPos].addr;
                }

                symbolsTable.push_back(tmp_symb2);

                 // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr+=3;
            }
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==NUM_DEC))
        {
            // Label + SPACE1
            int labelPos = findLabel(labelsTable,vtoks[0].string);
            if(labelPos==LABEL_NOT_FOUND)
            {
                // Insere Label na tabela de labels
                label tmp_label;
                tmp_label.text = vtoks[0].string;
                tmp_label.addr = currentSymbolAddr;

                labelsTable.push_back(tmp_label);
            }
            else
            {
                PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
            }

            // INST0
            int code = isValidInstructionCall(vtoks[2].string); // Considera SPACE0
            if(code==INVALID_INSTRUCTION)
            {
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
            else if(code==INVALID_ARG_NUMBER)
            {
                PRINT_ERR_ARG_NUM(lineCount,line);
            }
            else if(code==SPACE0)
            {
                if(currentSection!=SECTION_DATA)
                {
                    PRINT_ERR_WRONG_SECTION_DATA_INSTRUCTION(lineCount,line);
                }
                else
                {
                    // Acrescenta os espaços
                    int spaceAmount = atoi(vtoks[3].string.c_str());
                    for(int i=0;i<spaceAmount;i++)
                    {
                        symbol tmp_symb0;

                        tmp_symb0.type = SYM_NUM_DEC;
                        tmp_symb0.content = 0;
                        tmp_symb0.address = currentSymbolAddr+i;
                        symbolsTable.push_back(tmp_symb0);
                    }
                    currentSymbolAddr+=spaceAmount; // Atualiza Endereços
                }
            }
            else if(code==CONST)
            {
                if(currentSection!=SECTION_DATA)
                {
                    PRINT_ERR_WRONG_SECTION_DATA_INSTRUCTION(lineCount,line);
                }
                else
                {
                    symbol tmp_symb0;

                    tmp_symb0.type = SYM_NUM_DEC;
                    tmp_symb0.content = atoi(vtoks[3].string.c_str());
                    tmp_symb0.address = currentSymbolAddr+1;
                    symbolsTable.push_back(tmp_symb0);
                }
            }
            else
            {
                // Instrução Mal formatada
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else
        {
            // Instrução Mal formatada
            PRINT_ERR_INSTRUCTION(lineCount,line);

            #if DEBUG_PARSER
            for(vector<token>::iterator it = vtoks.begin(); it != vtoks.end();++it)
            {
                cout << (*it).type << '\t';
            }
            cout << endl;
            #endif
        }
    }

    // Verifica Existência da Seções TEXT
    if(!isSectionTextDeclared)
    {
        cerr << MSG_ERR_MISSING_SECTION_TEXT;
    }

    // Escrita no Arquivo
    for(vector<symbol>::iterator it = symbolsTable.begin(); it != symbolsTable.end();++it)
    {
        // Micro Passagem Para Atualizar Labels Pendentes
        if((*it).content==UNDEFINED_LABEL_ADDR)
        {
            int labelPos = findLabel(labelsTable,(*it).text);
            if(labelPos!=LABEL_NOT_FOUND)
            {
                // Atuliza Rótulos Pendentes
                (*it).content = labelsTable[labelPos].addr;
            }
            else
            {
                /// @todo Modificar Programa para permitir identificar linha do erro
                cerr << (*it).text << MSG_ERR_LABEL_UNDEFINED;
            }
        }
        else if((*it).content < -1) // Endereço de vetor não definido (Case +)
        {
          int labelPos = findLabel(labelsTable,(*it).text);
          if(labelPos!=LABEL_NOT_FOUND)
          {
              // Atuliza Rótulos Pendentes
              (*it).content = labelsTable[labelPos].addr - ((*it).content); //Recuperando o valor de numplus armazenado
          }
          else
          {
              /// @todo Modificar Programa para permitir identificar linha do erro
              cerr << (*it).text << MSG_ERR_LABEL_UNDEFINED;
          }
        }

        #if DEBUG_ASSEMBLER
            cout << (*it).content << ' ' << (*it).text << endl;
        #endif

        OutputFILE << (*it).content << ' ';
    }

    OutputFILE.close();
    InputFILE.close();

    // Gera código de erro
    return (errorDetected)?1:0;

 }
