#include "languagedefinition.h"
#include "parser.h"

int isValidInstructionCall(string command){
    // Pesquisa command na lista de funções definidas
    for (int i = 1; i <=INSTRUCTIONS_NUMBER; i++) {
        if (command.compare(InstrutionString[i]) == 0) {
            return (i+1);
        }
    }
    return INVALID_INSTRUCTION;
}

int isValidInstructionCall(string command, string arg1){
    int code = isValidInstructionCall(command);

    if(InstructionArgNumber[code-1]!=1)
    {
        return INVALID_ARG_NUMBER;
    }
    else if(isValidInstructionCall(arg1))
    {
        return INVALID_ARG1;
    }
    else
    {
        // Retorna INVALID_INSTRUCTION ou Código da instrução
        return code;
    }
}

int isValidInstructionCall(string command, string arg1,string arg2){
    int code = isValidInstructionCall(command);

    if(InstructionArgNumber[code-1]!=2)
    {
        return INVALID_ARG_NUMBER;
    }
    else if(isValidInstructionCall(arg1))
    {
        return INVALID_ARG1;
    }
    else if(isValidInstructionCall(arg2))
    {
        return INVALID_ARG2;
    }
    else
    {
        // Retorna INVALID_INSTRUCTION ou Código da instrução
        return code;
    }
}
