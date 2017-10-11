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

// Tabelas Internas
vector<symbol> symbolsTable;
vector<label> labelsTable;
int currentSymbolAddr = 1;

// Flags
bool isSectionTextDeclared = false;
bool isSectionDataDeclared = false;
SectionMode currentSection = SECTION_NONE;

bool lexicalAnalysisInstruction(int lineCount,string line,vector<token> vtoks,vector<symbol> *symbolsTb,vector<label> *labelsTb, int *currentSymbAd);

bool addNewLabel(string strLabel,int addrLabel,int lineCount,string line);
bool addNewSymbolINST0(string strInst0, int lineCount,string line);
bool addNewSymbolINST1(string strInst1,string strArg1, int lineCount,string line);
bool addNewSymbolINST2(string strInst2,string strArg1,string strArg2, int lineCount,string line);
bool addNewSymbolINST1NUM(string strInst1,int numArg1, int lineCount,string line);
bool addNewSymbolINST1PLUS(string strInst1,string strArg1,int numArg1Plus, int lineCount,string line);

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

    string line;
    bool errorDetected = false;

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
            addNewSymbolINST0(vtoks[0].string,lineCount,line);
        }
        else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD))
        {
            // INST1
            addNewSymbolINST1(vtoks[0].string,vtoks[1].string,lineCount,line);
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)\
              &&(vtoks[2].type==PLUS)&&(vtoks[3].type==NUM_DEC))
        {
            // INST1 PLUS
            int numArg1Plus=std::atoi(vtoks[3].string.c_str());
            addNewSymbolINST1PLUS(vtoks[0].string,vtoks[1].string,numArg1Plus,lineCount,line);
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD)\
                &&(vtoks[2].type==COMMA)&&(vtoks[3].type==WORD))
        {
            // INST 2
            addNewSymbolINST2(vtoks[0].string,vtoks[1].string,vtoks[3].string,lineCount,line);
        }
        else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON))
        {
            addNewLabel(vtoks[0].string,currentSymbolAddr,lineCount,line);
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
            addNewLabel(vtoks[0].string,currentSymbolAddr,lineCount,line);
            addNewSymbolINST0(vtoks[2].string,lineCount,line);
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD))
        {
            // Label + INST1
            addNewLabel(vtoks[0].string,currentSymbolAddr,lineCount,line);
            addNewSymbolINST1(vtoks[2].string,vtoks[3].string,lineCount,line);
        }
        else if((vtoks.size()==6)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD)&&(vtoks[4].type==PLUS)\
                &&(vtoks[5].type==NUM_DEC))
        {
            // Label + INST1 PLUS
            addNewLabel(vtoks[0].string,currentSymbolAddr,lineCount,line);

            int numArg1Plus=std::atoi(vtoks[5].string.c_str());
            addNewSymbolINST1PLUS(vtoks[2].string,vtoks[3].string,numArg1Plus,lineCount,line);
        }
        else if((vtoks.size()==6)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==WORD)&&(vtoks[4].type==COMMA)\
                &&(vtoks[5].type==WORD))
        {
            // Label + INST2
            addNewLabel(vtoks[0].string,currentSymbolAddr,lineCount,line);
            addNewSymbolINST2(vtoks[2].string,vtoks[3].string,vtoks[5].string,lineCount,line);
        }
        else if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
                &&(vtoks[2].type==WORD)&&(vtoks[3].type==NUM_DEC))
        {
            // Label
            addNewLabel(vtoks[0].string,currentSymbolAddr,lineCount,line);

            // INST1 NUM (SPACE1)
            int numArg1=std::atoi(vtoks[3].string.c_str());
            addNewSymbolINST1NUM(vtoks[2].string,numArg1,lineCount,line);
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

bool addNewLabel(string strLabel,int addrLabel,int lineCount,string line)
{
    if(isValidInstructionCall(strLabel)>0)
    {
        // Erro Uso de palavra chave como Rótulo
        PRINT_ERR_LABEL(lineCount,line);
        return 1;
    }
    else if(findLabel(labelsTable,strLabel)!=LABEL_NOT_FOUND)
    {
        // Erro Rótulo Duplicado
        PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
        return 1;
    }
    else
    {
        // Insere Label na tabela de labels
        label tmp_label;
        tmp_label.text = strLabel;
        tmp_label.addr = addrLabel;

        labelsTable.push_back(tmp_label);
        return 0;
    }
}

bool addNewSymbolINST0(string strInst0, int lineCount,string line)
{
    int code = isValidInstructionCall(strInst0);
    if(code==INVALID_INSTRUCTION)
    {
        PRINT_ERR_INSTRUCTION(lineCount,line);
        return 1;
    }
    else if(code<=14)// Instrução Chamada de Instrução Válida
    {
        // Cria Simbolo e coloca na tabela
        symbol tmp_symb;
        tmp_symb.type = SYM_INSTRUCTION;
        tmp_symb.content = code;
        tmp_symb.address = currentSymbolAddr;
        symbolsTable.push_back(tmp_symb);

        // Atualiza Endereço p/ próximo simbolo
        currentSymbolAddr++;

        // Verifica se Instrução está na sessão certa
        if(currentSection!=SECTION_TEXT)
            PRINT_ERR_WRONG_SECTION_TEXT_INSTRUCTION(lineCount,line);
    }
    else // Possível Diretiva
    {
        switch (code) {
            case SPACE0:
            {
                symbol tmp_symb;
                tmp_symb.type = SYM_INSTRUCTION;
                tmp_symb.content = 0;
                tmp_symb.address = currentSymbolAddr;
                symbolsTable.push_back(tmp_symb);

                // Atualiza Endereço p/ próximo simbolo
                currentSymbolAddr++;

                // Verifica se a diretiva está na sessão certa
                if(currentSection!=SECTION_DATA)
                    PRINT_ERR_WRONG_SECTION_DATA_INSTRUCTION(lineCount,line);
            }
            default:
                // Ignora demais diretivas
                break;
        }
    }
    return 0;
}

bool addNewSymbolINST1(string strInst1,string strArg1, int lineCount,string line)
{
    int code = isValidInstructionCall(strInst1,strArg1);
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
        PRINT_ERR_ARG(lineCount,line,strArg1);
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

        labelPos = findLabel(labelsTable,strArg1);
        if(labelPos==LABEL_NOT_FOUND)
        {
            tmp_symb1.content = UNDEFINED_LABEL_ADDR;
            tmp_symb1.text = strArg1;
            /// @todo Modificar para permitir completar tabela ao final da passagem
        }
        else
        {
            tmp_symb1.content = labelsTable[labelPos].addr;
        }

        symbolsTable.push_back(tmp_symb1);

         // Atualiza Endereço p/ próximo simbolo
        currentSymbolAddr+=2;

        // Verifica se Instrução está na sessão certa
        if(currentSection!=SECTION_TEXT)
            PRINT_ERR_WRONG_SECTION_TEXT_INSTRUCTION(lineCount,line);
    }
    else
    {
        // Possível Diretiva
        switch (code) {
            case SECTION:
                if(strArg1=="TEXT")
                {
                    isSectionTextDeclared = true;
                    currentSection = SECTION_TEXT;
                }
                else if(strArg1=="DATA")
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
                int spaceAmount = atoi(strArg1.c_str());
                for(int i=0;i<spaceAmount;i++)
                {
                    symbol tmp_symb0;

                    tmp_symb0.type = SYM_NUM_DEC;
                    tmp_symb0.content = 0;
                    tmp_symb0.address = currentSymbolAddr+i;
                    symbolsTable.push_back(tmp_symb0);
                }
                currentSymbolAddr+=spaceAmount; // Atualiza Endereços

                // Verifica se a Diretiva está na sessão certa
                if(currentSection!=SECTION_DATA)
                    PRINT_ERR_WRONG_SECTION_DATA_INSTRUCTION(lineCount,line);
                break;
            }
            case CONST:
                // Erro
                PRINT_ERR_ARG(lineCount,line,strArg1);

                // Verifica se a Diretiva está na sessão certa
                if(currentSection!=SECTION_DATA)
                    PRINT_ERR_WRONG_SECTION_DATA_INSTRUCTION(lineCount,line);
                break;
        }
    }
}

bool addNewSymbolINST1PLUS(string strInst1,string strArg1,int numArg1Plus, int lineCount,string line)
{
    int code = isValidInstructionCall(strInst1,strArg1);
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
      PRINT_ERR_ARG(lineCount,line,strArg1);
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

      labelPos = findLabel(labelsTable,strArg1);
      if(labelPos==LABEL_NOT_FOUND)
      {
          tmp_symb1.content = -1-numArg1Plus; //Armazena como negativo para recuperar o numero depois
          tmp_symb1.text = strArg1;
          /// @todo Modificar para permitir completar tabela ao final da passagem
      }
      else
      {
          tmp_symb1.content = labelsTable[labelPos].addr+numArg1Plus;
      }

      symbolsTable.push_back(tmp_symb1);

       // Atualiza Endereço p/ próximo simbolo
      currentSymbolAddr+=2;

      // Verifica se Instrução está na sessão certa
      if(currentSection!=SECTION_TEXT)
          PRINT_ERR_WRONG_SECTION_TEXT_INSTRUCTION(lineCount,line);
    }
    else // Possível Diretiva
    {
        PRINT_ERR_INSTRUCTION(lineCount, line);
    }
}

bool addNewSymbolINST1NUM(string strInst1,int numArg1, int lineCount,string line)
{
    int code = isValidInstructionCall(strInst1); // Considera SPACE0
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
            int spaceAmount = numArg1;
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
            tmp_symb0.content = numArg1;
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

bool addNewSymbolINST2(string strInst2,string strArg1,string strArg2, int lineCount,string line)
{
    int code = isValidInstructionCall(strInst2,strArg1,strArg2);
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
        PRINT_ERR_ARG(lineCount,line,strArg1);
    }
    else if(code==INVALID_ARG2)
    {
        PRINT_ERR_ARG(lineCount,line,strArg2);
    }
    else if(code<=14) // Chamada Válida de instrução
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

        labelPos = findLabel(labelsTable,strArg1);
        if(labelPos==LABEL_NOT_FOUND)
        {
            tmp_symb1.content = UNDEFINED_LABEL_ADDR;
            tmp_symb1.text = strArg1;
            /// @todo Modificar para permitir completar tabela ao final da passagem
        }
        else
        {
            tmp_symb1.content = labelsTable[labelPos].addr;
        }

        symbolsTable.push_back(tmp_symb1);

        tmp_symb2.type = SYM_LABEL;

        labelPos = findLabel(labelsTable,strArg2);
        if(labelPos==LABEL_NOT_FOUND)
        {
            tmp_symb2.content = UNDEFINED_LABEL_ADDR;
            tmp_symb2.text = strArg2;
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

        if(currentSection!=SECTION_TEXT)
            PRINT_ERR_WRONG_SECTION_TEXT_INSTRUCTION(lineCount,line);
    }
}
