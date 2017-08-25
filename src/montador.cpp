/**
 * Montador
 *
 * @author Rafael e Willian
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>

#include "montador.h"
#include "preprocessador.h"
#include "mensagens.h"

using namespace std;

int montador(int argc, char * argv[]){

    string arquivo_entrada = argv[2];
    string arquivo_saida   = argv[3];

    ifstream ArquivoASM(arquivo_entrada.c_str()); // input
    ofstream ArquivoPRE(arquivo_saida.c_str()); // output

    // Teste se ambos os aquivos foram abertos corretamente
    if (!(ArquivoASM.is_open() && ArquivoPRE.is_open()))
    {
        cout << MSG_ERRO_ARQUIVO;
        return 1;
    }

 }
