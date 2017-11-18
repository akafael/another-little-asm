/**
 * Pré-Compilador
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "lexer.h"
#include "msgs_pt.h"
#include "macroeval.h"

using namespace std;

int macroeval(string input_file, string output_file)
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
    vector<labelMacro> macroDefinitionTable;
    labelMacro tmpMacroDef;

    int currentStateMacroEval = MACROEV_READING_LINE;

    // Percorre todas as linhas do arquivo
    for(int lineCount=0;getline(ArquivoASM,line);lineCount++)
    {
       /// @todo Fazer validação das macros, IF e EQV

       vector<token> vtoks = tokenizer(line);

       // Verifica Sintaxe MACRO
       if((vtoks.size()==3)&&(vtoks[0].type==WORD)&&(vtoks[1].type==COLON)\
          &&(vtoks[2].type==WORD)&&(vtoks[2].string.compare("MACRO")==0))
       {
           int macroPos = findMacroDefinition(macroDefinitionTable,vtoks[0].string);
           if(macroPos==MACRO_NOT_FOUND)
           {
               tmpMacroDef.text = vtoks[0].string;
               tmpMacroDef.content = ""; // Esvazia conteúdo
               line="";  // Esvazia linha

               currentStateMacroEval = MACROEV_WRITING_MACRO;
           }
           else
           {
               PRINT_ERR_LABEL_DUPLICATED(lineCount,line);
           }
       }// Verifica Sintaxe ENDMACRO:
       else if((vtoks.size()==1)&&(vtoks[0].type==WORD)\
           &&(vtoks[0].string.compare("ENDMACRO")==0))
       {
           currentStateMacroEval = MACROEV_READING_LINE;
           macroDefinitionTable.push_back(tmpMacroDef);
           line="";  // Esvazia linha
       }
       else if((vtoks.size()!=0))
       {
           /// @todo Verificar uso das MACROS

          for(vector<token>::iterator it = vtoks.begin(); it != vtoks.end();++it)
          {
              int macroPos = findMacroDefinition(macroDefinitionTable,(*it).string);
              if(macroPos!=MACRO_NOT_FOUND)
              {
                  line=""; // Apaga Linha com chamada da Macro
                  /// @todo Verificar necessidade de quebra de linha
                   ArquivoPRE << macroDefinitionTable[macroPos].content;
              }
          }

       }

       if(currentStateMacroEval==MACROEV_WRITING_MACRO)
       {
           tmpMacroDef.content += line + '\n';
       }
       else if(currentStateMacroEval==MACROEV_READING_LINE)
       {
           // Escreve linha no arquivo de saída
           ArquivoPRE << line << '\n';
       }
    }

    ArquivoPRE.close();
    ArquivoASM.close();

    return 0;
}

int findMacroDefinition(vector<labelMacro> macroDefinitionTable,string macroText)
{
    for (int i = 0; i < macroDefinitionTable.size(); i++)
    {
        if(macroText.compare(macroDefinitionTable[i].text)==0)
        {
            return i;
        }
    }
    return MACRO_NOT_FOUND;
}
