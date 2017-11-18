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

    // Ler Arquivo
    string strFileName, strSize, strHeaderRef, strTextSegment;
    getline(fileEXE,strFileName);
    getline(fileEXE,strSize);
    getline(fileEXE,strHeaderRef);
    getline(fileEXE,strTextSegment);

    // Gera vetor para a fita de instruções
    vector<token> vtoks = tokenizer(strTextSegment);
    vtoks.erase(vtoks.begin(),vtoks.begin()+2); // Remove "T:"
    vector<int> vData;
    for(vector<token>::iterator it = vtoks.begin(); it < vtoks.end();++it)
    {
        // Converte todos os valores de dados para int
        vData.push_back(atoi((*it).string.c_str()));
        if(vData.back()<0)
        {
            return 0;
        }
    }

    // Inicializa o Processador
    mProcessor.accReg = 0;
    mProcessor.pcReg = 1;
    bool flagKeepProcessorRunning = true;

    while(flagKeepProcessorRunning)
    {
        // Ilustra os Registradores do Processador
        cout << "PROCESSOR => ACC: " << mProcessor.accReg ;
        cout << " PC: " << mProcessor.pcReg << endl;

        // Decodifica Instrução
        int data = vData.at(mProcessor.pcReg-1);
        int numParam = InstructionArgNumber[data-1];

        // Ilustra a Leitura da Função
        cout << ".." << InstrutionString[data-1];
        if(numParam>0)
            cout << ' ' << vData.at(mProcessor.pcReg);
        if(numParam>1)
            cout << ' ' << vData.at(mProcessor.pcReg+1);
        cout << endl;

        // Executa a Instrução de Acordo com o Opcode
        switch (data) {
            case ADD:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                mProcessor.accReg += vData.at(arg1-1);
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case SUB:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                mProcessor.accReg -= vData.at(arg1-1);
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case MULT:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                mProcessor.accReg *= vData.at(arg1-1);
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case DIV:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                mProcessor.accReg /= vData.at(arg1-1);
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case JMP:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                mProcessor.pcReg=arg1;
                break;
            }
            case JMPN:
            {
                if(mProcessor.accReg<0)
                {
                    int arg1 = vData.at(mProcessor.pcReg);
                    mProcessor.pcReg=arg1;
                }
                else
                {
                    mProcessor.pcReg+=numParam+1;
                }
                break;
            }
            case JMPP:
            {
                if(mProcessor.accReg>0)
                {
                    int arg1 = vData.at(mProcessor.pcReg);
                    mProcessor.pcReg=arg1;
                }
                else
                {
                    mProcessor.pcReg+=numParam+1;
                }
                break;
            }
            case JMPZ:
            {
                if(mProcessor.accReg==0)
                {
                    int arg1 = vData.at(mProcessor.pcReg);
                    mProcessor.pcReg=arg1;
                }
                else
                {
                    mProcessor.pcReg+=numParam+1;
                }
                break;
            }
            case COPY:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                int arg2 = vData.at(mProcessor.pcReg+1);
                vData.at(arg2)= vData.at(arg1);
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case LOAD:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                mProcessor.accReg = vData.at(arg1-1);
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case STORE:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                vData.at(arg1-1) = mProcessor.accReg;
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case INPUT:
            {
                string strNum;
                cin >> strNum;
                int arg1 = vData.at(mProcessor.pcReg);
                vData.at(arg1-1) = atoi(strNum.c_str());
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case OUTPUT:
            {
                int arg1 = vData.at(mProcessor.pcReg);
                cout << vData.at(arg1-1) << endl;
                mProcessor.pcReg+=numParam+1;
                break;
            }
            case STOP:
            {
                flagKeepProcessorRunning = false; // Pula para o final
                break;
            }
            default:
            {
                // Op code Inválido
                cerr << MSG_ERR_INVALID_INSTRUCTION;
                flagKeepProcessorRunning = false; // Pula para o final
            }
        }
    }

    cout << endl;
    return 0;
}
