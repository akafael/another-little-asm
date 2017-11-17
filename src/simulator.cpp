/**
 * Processor Simulator
 * Emula uma pequena máquina de turing com dois registradores
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "lexer.h"
#include "msgs_pt.h"
#include "languagedefinition.h"

using namespace std;

typedef struct
{
    int accReg; ///< Acumulator
    int pcReg; ///< Program Counter
} mini_processor;

typedef struct
{
    bool isRelativeAddr;
    int value;
} dataUnit;

typedef enum{
    DATA_INST = 0,
    DATA_REF = 1,
    DATA_DATA = 2
} readMode;

int simulator(string input_file)
{
    mini_processor mProcessor;
    ifstream fileEXE(input_file.c_str());

    // Teste se o aquivo foi aberto corretamente;
    if (!(fileEXE.is_open()))
    {
        cout << MSG_ERR_FILE;
        return 1;
    }

    string strFileName, strSize, strHeaderRef, strTextSegment;
    getline(fileEXE,strFileName);
    getline(fileEXE,strSize);
    getline(fileEXE,strHeaderRef);
    getline(fileEXE,strTextSegment);

    // Gera vetor para a fita de instruções
    vector<token> vtoks = tokenizer(strTextSegment);
    vtoks.erase(vtoks.begin(),vtoks.begin()+2); // Remove "T:"

    // Inicializa o Processador
    mProcessor.accReg = 0;
    mProcessor.pcReg = 1;

    for(vector<token>::iterator it = vtoks.begin(); it < vtoks.end();++it)
    {
        // Ilustra os Registradores do Processador
        cout << "PROCESSOR => ACC: " << mProcessor.accReg ;
        cout << " PC: " << mProcessor.pcReg << endl;
        cout << '\t' << (*it).string << endl;

        // Decodifica a Instrução
        int data = atoi((*it).string.c_str());
        int numParam = InstructionArgNumber[data-1];

        // Executa a Instrução decodificada
        switch (data) {
            case ADD :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                mProcessor.accReg += atoi(vtoks.at(arg1-1).string.c_str());
                break;
            }
            case SUB :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                mProcessor.accReg -= atoi(vtoks.at(arg1-1).string.c_str());
                break;
            }
            case MULT :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                mProcessor.accReg *= atoi(vtoks.at(arg1-1).string.c_str());
                break;
            }
            case DIV :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                mProcessor.accReg /= atoi(vtoks.at(arg1-1).string.c_str());
                break;
            }
            case JMP :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                it = vtoks.begin() + arg1 - numParam;
                break;
            }
            case JMPN :
            {
                if(mProcessor.accReg<=0)
                {
                    int arg1 = atoi((*(it+1)).string.c_str());
                    it = vtoks.begin() + arg1 - numParam;
                }
                break;
            }
            case JMPP :
            {
                if(mProcessor.accReg>=0)
                {
                    int arg1 = atoi((*(it+1)).string.c_str());
                    it = vtoks.begin() + arg1 - numParam;
                }
                break;
            }
            case JMPZ :
            {
                if(mProcessor.accReg==0)
                {
                    int arg1 = atoi((*(it+1)).string.c_str());
                    it = vtoks.begin() + arg1 - numParam;
                }
                break;
            }
            case COPY :
            {
                (*(it+2)).string = (*(it+1)).string;
                break;
            }
            case LOAD :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                int refData = atoi(vtoks.at(arg1-1).string.c_str());
                mProcessor.accReg = refData;
                break;
            }
            case STORE :
            {
                std::ostringstream ss;
                ss << mProcessor.accReg;
                (*(it+1)).string = ss.str();
                break;
            }
            case INPUT :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                cin >> vtoks.at(arg1-1).string;
                break;
            }
            case OUTPUT :
            {
                int arg1 = atoi((*(it+1)).string.c_str());
                cout << arg1 << endl;
                break;
            }
            case STOP :
            {
                // Encerra o programa
                it = vtoks.end();
                break;
            }
        }

        // Atualiza Program Counter
        it += numParam;
        mProcessor.pcReg = it - vtoks.begin();
    }

    cout << endl;
    return 0;
}
