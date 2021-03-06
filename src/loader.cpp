/**
 * Loader
 *
 * @authors Rafael Lima, João Paulo Franch , Túlio Lima
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "lexer.h"
#include "msgs_pt.h"
#include "simulator.h"

typedef struct{
    int startAddr;
    int size;
} men_chunk;

using namespace std;

int main(int argc, char** argv)
{
    if (argc< 4)
    {
        cout << MSG_ERR_LOADER_ARGUMENT_NUMBER;
        return 1;
    }
    else
    {
        int chunksNum = atoi(argv[2]);

        // Verificando Quantidade de Argumentos
        if(argc != (2*chunksNum + 3))
        {
            cout << MSG_ERR_LOADER_ARGUMENT_NUMBER;
            return 1;
        }

        ifstream fileEXE(argv[1]); // input

        // Teste se o aquivo de entrada foi aberto corretamente;
        if (!(fileEXE.is_open()))
        {
            cout << MSG_ERR_FILE;
            return 1;
        }

        // Ler Arquivo
        string strFileName, strSize, strHeaderRef, strTextSegment;
        getline(fileEXE,strFileName);
        // Pega apenas o nome do arquivo para criar o arquivo de saída
        strFileName=strFileName.substr(3,strFileName.size());
        getline(fileEXE,strSize);
        int codeSize = atoi(strSize.substr(3,strSize.size()).c_str());

        getline(fileEXE,strHeaderRef);
        strHeaderRef += strHeaderRef.substr(3,strHeaderRef.size());
        getline(fileEXE,strTextSegment);

        fileEXE.close();

        // Vetor com os tokens do código objeto
        std::vector<token> vtoks = tokenizer(strTextSegment);
        vtoks.erase(vtoks.begin(),vtoks.begin()+2); // Remove o T:
        std::vector<int> vData;
        for(std::vector<token>::iterator it = vtoks.begin(); it < vtoks.end();++it){
            // Converte todos os valores de dados para int
            vData.push_back(atoi((*it).string.c_str()));
        }

        // Variáveis de conferência de tamanhos de memória
        int allocRemainingSize=codeSize;

        // Laço para cálculo do tamanho de memória necessário de acordo com os argumentos do comando
        for(int i = 0,addrPos=0; i < chunksNum; i++)
        {
            /// @todo Verificar Tipo dos Argumentos (valores inteiros positivos)
            // Esse todo pode naõ ser necessário.
            /// @todo Verificar Sobreposição de Chunks (se o endereço de inicio de um chunk está contido em algum espaço anterior)

            int addrBase = atoi(argv[3+chunksNum+i]);
            int sizeMenChunk = atoi(argv[3+i]);
            allocRemainingSize=allocRemainingSize-sizeMenChunk;

            string fileName = argv[1];
            fileName += std::to_string(i) + ".im";
            ofstream fileOUT(fileName.c_str());

            // Escreve no Arquivo
            int addrFinal = sizeMenChunk + addrPos;
            for(int j = addrPos;(j < addrFinal) && (j < vData.size()); j++)
            {
                // Atualiza Endereços Relativos
                if(strHeaderRef.at(j)=='1')
                    vData[j] += addrBase;

                fileOUT << vData[j] << ' ';
            }
            addrPos+=sizeMenChunk;

            fileOUT.close();

            // calcula se o tamanho disponível em cada chunk é suficiente
            /// @todo checar se a conferência geral já não resolve
            /// @todo verificar se caso não haja espaço se os dados são distribuídos entre os chunks de memória
            if((allocRemainingSize-sizeMenChunk)<0)
            {
                // Tamanho suficiente de memoria
                allocRemainingSize=0;
                break;
            }
        }

        if(allocRemainingSize>0)
        {
          cout << MSG_ERR_LOADER_ALLOCATION;
          return 1;
        }

        // Executa simulador
        simulator(argv[1]);
    }

    return 0;
}
