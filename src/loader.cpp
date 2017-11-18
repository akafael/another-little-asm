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

        vector<ofstream> vFileOUT;

        for(int i = 0; i < chunksNum; i++)
        {
            /// @todo Verificar Tipo dos Argumentos (valores inteiros positivos)
            /// @todo Verificar Sobreposição de Chunks (se o endereço de inicio de um chunk está contido em algum espaço anterior)
            /// @todo Verificar se a soma dos chunks é suficiente para o programa
            /// @todo Criar arquivos de saída
        }

        /// @todo Percorrer Arquivo de Entrada e atualizar endereços relativos

        fileEXE.close();

        simulator(argv[1]);
    }

    return 0;
}
