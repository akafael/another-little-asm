/**
 * Loader
 *
 * @authors Rafael Lima, João Paulo Franch , Túlio
 */

 #include <string>
 #include <algorithm>
 #include <vector>

typedef struct{
    int startAddr;
    int size;
} men_chunk;

int main(int argc, char** argv)
{
    if (argc< 3)
    {
        cout << MSG_ERR_LOADER_ARGUMENT_NUMBER;
        return 1;
    }
    else
    {
        int chunksNum = atoi(argv[2]);
        vector<men_chunk> vChunks;

        // Verificando Quantidade de Argumentos
        if(argc < (2*chunksNum + 2))
        {
            cout << MSG_ERR_LOADER_ARGUMENT_NUMBER;
            return 1;
        }

        ifstream fileEXE(argv[1]); // input

        // Teste se o aquivo de entrada foi aberto corretamente;
        if (!(fileEXE.is_open())
        {
            cout << MSG_ERR_FILE;
            return 1;
        }

        vector<ofstream> vFileOut; // Arquivos de saída

        for(int i = 0; i < chunksNum; i++)
        {
            /// @todo Verificar Tipo dos Argumentos (valores inteiros positivos)
            /// @todo Verificar Sobreposição de Chunks (se o endereço de inicio de um chunk está contido em algum espaço anterior)
            men_chunk tmp_chunk;
            tmp_chunk.startAddr = atoi(argv[3+i]);
            tmp_chunk.size = atoi(argv[3+chunksNum+i]);

            vChunks.add(tmp_chunk);

            /// @todo Criar um arquivo de saída
        }

        ///@ todo Percorrer Arquivo de Entrada e atualizar endereços relativos

    }

    return 0;
}
