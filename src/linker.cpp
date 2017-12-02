/**
 * Linker
 *
 * @authors Rafael Lima, João Paulo Franch , Túlio
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "msgs_pt.h"
#include "lexer.h"
#include "parser.h"

typedef struct{
    int startAddr;
    int size;
} men_chunk;

vector<label> labelDefTable; ///< Tabela de Definições
vector<label> labelUseTable; ///< Tabela de Uso

using namespace std;

int main(int argc, char** argv)
{
    if (argc< 2)
    {
        std::cout << MSG_ERR;
        return 1;
    }
    else if(argc == 2) // Caso Trivial Ligador Dispensado
    {
        string inputFileName = argv[1];

        // Remove extensão do arquivo
        string baseName = inputFileName;
        int charPosition = baseName.rfind('.');
        if(charPosition != std::string::npos)
            baseName = baseName.substr(0,charPosition);

        string outputFileName = baseName + ".obj";

        ifstream InputFILE(inputFileName.c_str()); // input;
        ofstream OutputFILE(outputFileName.c_str()); // output;

        // Teste se ambos os aquivos foram abertos corretamente;
        if (!(InputFILE.is_open() && OutputFILE.is_open()))
        {
            cerr << MSG_ERR_FILE;
            return 1;
        }

        string line;
        for(int lineCount = 0; getline(InputFILE,line);lineCount++)
        {
            OutputFILE << line << endl;
        }

        /// @todo Mostrar Erro Caso Existam tabelas de Definição e de Uso

        InputFILE.close();
        OutputFILE.close();
    }
    else if (argc >= 3)
    {
        string strFileName, strSize, strHeaderRef, strTextSegment;
        ostringstream ssTextSegment;
        int finalSize = 0;
        vector<int> vData;

        for(int j = 1, addrBase = 0; j < argc ; j++)
        {
            ifstream InputFILE(argv[j]);

            if (!(InputFILE.is_open()))
            {
                cerr << MSG_ERR_FILE << argv[j];
                return 1;
            }

            // Ler Arquivo
            string line;
            getline(InputFILE,line);
            strFileName = line + " ";

            getline(InputFILE,line);
            int sizeTextSegment = atoi(line.substr(3,line.size()).c_str());
            finalSize+=sizeTextSegment;

            // Mescla Header
            getline(InputFILE,line);
            strHeaderRef += line.substr(3,line.size());

            getline(InputFILE,line);
            string tmpTextSegment = line;

            // Ler Tabela de uso
            if(getline(InputFILE,line))
            {
                string strTable = line.substr(4,line.size());
                vector<token> vtoksU = tokenizer(tmpTextSegment);
                for(vector<token>::iterator it = vtoksU.begin(); it < vtoksU.end();it+=3)
                {
                    if((vtoksU.size()==4)&&(vtoksU[0].type==WORD)&&(vtoksU[1].type==WORD)\
                          &&(vtoksU[2].type==NUM_DEC))
                    {
                        label tmp_label;
                        tmp_label.text = (*it).string;
                        tmp_label.value = atoi((*(it+2)).string.c_str())+addrBase;

                        labelUseTable.push_back(tmp_label);
                    }
                }
            }

            // Ler Tabela de Definições
            if(getline(InputFILE,line))
            {
                string strTable = line.substr(4,line.size());
                vector<token> vtoksU = tokenizer(tmpTextSegment);
                for(vector<token>::iterator it = vtoksU.begin(); it < vtoksU.end();it+=3)
                {
                    if((vtoksU.size()==4)&&(vtoksU[0].type==WORD)&&(vtoksU[1].type==WORD)\
                          &&(vtoksU[2].type==NUM_DEC))
                    {
                        label tmp_label;
                        tmp_label.text = (*it).string;
                        tmp_label.value = atoi((*(it+2)).string.c_str())+addrBase;

                        labelDefTable.push_back(tmp_label);
                    }
                }
            }

            // Gera vetor do segmento de instruções
            vector<token> vtoks = tokenizer(tmpTextSegment);
            vtoks.erase(vtoks.begin(),vtoks.begin()+2); // Remove "T:"
            for(vector<token>::iterator it = vtoks.begin(); it < vtoks.end();++it){
                // Converte todos os valores de dados para int
                vData.push_back(atoi((*it).string.c_str()));
            }

            for(int i=addrBase;i< finalSize;i++)
            {
                // Atualiza Endereço da demais posições
                if(strHeaderRef.at(i)=='1')
                    vData[i] += addrBase;
            }

            addrBase = finalSize;
            InputFILE.close();
        }

        // Pesquisa Valores da tabela de uso nas tabelas de definições
        for (int i = 0; i <labelUseTable.size(); i++)
        {
            int labelPos = findLabel(labelDefTable,labelUseTable[i].text);
            if(labelPos==LABEL_NOT_FOUND)
            {
                cerr << labelUseTable[i].text << MSG_ERR_LABEL_UNDEFINED;
            }
            else
            {
                // Atualiza Dados no Segmento de Texto
                vData[labelUseTable[i].value-1] = labelDefTable[labelPos].value;
            }
        }

        // Constroi novo segmento de texto
        for (int i = 0; i <vData.size(); i++)
        {
            ssTextSegment << vData[i] << ' ';
        }

        string inputFileName = argv[1];

        // Remove extensão do arquivo
        string baseName = inputFileName;
        int charPosition = baseName.rfind('.');
        if(charPosition != std::string::npos)
            baseName = baseName.substr(0,charPosition);

        string outputFileName = baseName;

        ofstream OutputFILE(outputFileName.c_str()); // output;

        // Teste se ambos os aquivos foram abertos corretamente;
        if (!(OutputFILE.is_open()))
        {
            cerr << MSG_ERR_FILE;
            return 1;
        }

        OutputFILE << strFileName << endl;
        OutputFILE << "H: " << finalSize << endl;
        OutputFILE << "H: " << strHeaderRef << endl;
        OutputFILE << "T: " << ssTextSegment.str() << endl;

        OutputFILE.close();
    }

    return 0;
}
