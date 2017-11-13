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
#include "lexer.h"
#include "preprocessor.h"

using namespace std;

typedef struct{
    token tok;
    string text;
}labelDir;

int findLabelDir(vector<labelDir> labelTable,string labelText);

int preprocessor(string input_file, string output_file)
{

    ifstream ArquivoASM(input_file.c_str()); // input;
    ofstream ArquivoPRE(output_file.c_str()); // output;

    // Teste se ambos os aquivos foram abertos corretamente;
    if (!(ArquivoASM.is_open() && ArquivoPRE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    string line;
    bool errorDetected = false;
    vector<labelDir> labelsTable;

    // Percorre todas as linhas do arquivo
    for(int lineCount=0;getline(ArquivoASM,line);lineCount++)
    {
        bool ignoreLine = false;
        int charPosition;

        // Deixa todos caracteres em caixa alta
        std::transform(line.begin(), line.end(),line.begin(), ::toupper);

        // Detecta e Remove Comentários
        charPosition = line.find(';');
        if(charPosition != std::string::npos){
            // Caso achou a string
            line = line.substr(0,charPosition);
        }

        // Detecta EQU e verifica sintaxe
        charPosition = line.find("EQU");
        if(charPosition != std::string::npos){
            // Caso achou a string
            vector<token> vtoks = tokenizer(line);
            ignoreLine = true; // Ignora linha por ser diretiva

            if((vtoks.size()==4)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
               &&(vtoks[2].type==WORD)&&((vtoks[3].type==NUM_DEC)||(vtoks[3].type==WORD)))
            {
                int labelPos = findLabelDir(labelsTable,vtoks[0].string);
                if(labelPos==LABELDIR_NOT_FOUND)
                {
                    // Insere Label na tabela de labels
                    labelDir tmp_labelDir;
                    tmp_labelDir.text = vtoks[0].string;
                    tmp_labelDir.tok = vtoks[3];

                    labelsTable.push_back(tmp_labelDir);
                }
                else
                {
                    PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
                }
            }
            else
            {
                // Uso Incorreto do EQU
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }

        // Detecta IF e verifica sintaxe
        charPosition = line.find("IF");
        if(charPosition!=std::string::npos){
            // Caso achou a string
            vector<token> vtoks = tokenizer(line);
            ignoreLine = true; // Ignora linha por ser diretiva

            if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==WORD))
            {
                // Procura Rótulo na Tabela de Rótulos
                int labelPos = findLabelDir(labelsTable,vtoks[1].string);
                if(labelPos!=LABELDIR_NOT_FOUND)
                {
                    string labelText = labelsTable[labelPos].text;
                    token tmp_token = labelsTable[labelPos].tok;

                    // Verifica Sintaxe do uso da diretiva
                    if(tmp_token.type==NUM_DEC)
                    {
                        if(std::atoi(tmp_token.string.c_str())==0)
                        {
                            // Descarta Linha
                            string trashLine;
                            getline(ArquivoASM,trashLine);
                        }
                    }
                    else
                    {
                        PRINT_ERR_IF(lineCount,line);
                    }
                }
                else
                {
                    PRINT_ERR_LABEL(lineCount,line);
                }
            }
            else if((vtoks.size()==2)&&(vtoks[0].type==WORD)&&(vtoks[1].type==NUM_DEC))
            {
                // Verifica Número
                if(std::atoi(vtoks[2].string.c_str())==0)
                {
                    // Descarta Linha
                    string trashLine;
                    getline(ArquivoASM,trashLine);
                }
            }
            else
            {
                // Uso Incorreto do IF
                PRINT_ERR_INSTRUCTION(lineCount,line);
            }
        }
        else
        {
            // Pesquisa Existência de rótulos na linha
            for (int i = 0; i <labelsTable.size(); i++)
            {
                string tmpLabel = labelsTable[i].text;
                charPosition = line.find(tmpLabel);
                if(charPosition != std::string::npos){
                    // Caso achou a string
                    line = line.substr(0,charPosition)+tmpLabel\
                       +line.substr(charPosition+tmpLabel.size(),line.size());
                }
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

int findLabelDir(vector<labelDir> labelTable,string labelText)
{
    for (int i = 0; i <labelTable.size(); i++)
    {
        if(labelTable[i].text.compare(labelText)==0)
        {
            return i;
        }
    }
    return LABELDIR_NOT_FOUND;
}
