/**
 * Loader
 *
 * @authors Rafael Lima, João Paulo Franch , Túlio
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
        getline(fileEXE,strHeaderRef);
        getline(fileEXE,strTextSegment);
        strSize.size();

        // Vetor com os tokens do código objeto
        vector<token> vsize = tokenizer(strSize);
        vsize.erase(vsize.begin(),vsize.begin()+2); // Remove o T:

        // Variaveis de conferência de tamanhos de memória
        int codeSize = atoi(vsize[0].string.c_str());
        int allocRemainingSize=codeSize;

        // Laço para cálculo do tamanho de memória necessário de acordo com os argumentos do comando
        for(int i = 0; i < chunksNum; i++)
        {
            /// @todo Verificar Tipo dos Argumentos (valores inteiros positivos)

            int sizeMenChunk = atoi(argv[3+i]);
            // Inicializa cada arquivo de saida a medida que calcula se o tamanho disponível em cada chunk é suficiente
            if((allocRemainingSize-sizeMenChunk)>0){
              allocRemainingSize=allocRemainingSize-sizeMenChunk;
              /// @todo Criar arquivos de saída com nomes diferentes usando a variável i(converter de inteiro para string)
              string fileName = strFileName + "generico";
              ofstream fileOUT(fileName.c_str());
              fileOUT.close();
            }
            else
            {
              allocRemainingSize=allocRemainingSize-sizeMenChunk;
              // Tamanho suficiente de memoria
              break;
            }

            /// @todo Verificar Sobreposição de Chunks (se o endereço de inicio de um chunk está contido em algum espaço anterior)

        }

        fileEXE.close();

        if(allocRemainingSize>0)
        {
          cout << MSG_ERR_LOADER_ALLOCATION;
          return 1;
        }

        /// @todo Percorrer Arquivo de Entrada e atualizar endereços relativos



        simulator(argv[1]);
    }

    return 0;
}
