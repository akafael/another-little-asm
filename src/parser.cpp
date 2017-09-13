#include "languagedefinition.h"
#include "parser.h"

int isValidInstructionCall(string command){
    for (int i = 1; i <=INSTRUCTIONS_NUMBER; i++) {
        if (command.compare(InstrutionString[i]) == 0) {
            return (i+1);
        }
    }
    return INVALID_INSTRUCTION;
}

int isValidInstructionCall(string command, string arg1){
    int code = isValidInstructionCall(command);

    if(code==INVALID_INSTRUCTION)
    {
        return false;
    }
    else
    {
        if((InstructionArgNumber[code-1]==1)&&!isValidInstructionCall(arg1))
        {
            return code;
        }
        else
        {
            return false;
        }
    }
}

int isValidInstructionCall(string command, string arg1,string arg2){
    int code = isValidInstructionCall(command);

    if(code==INVALID_INSTRUCTION)
    {
        return false;
    }
    else
    {
        if((InstructionArgNumber[code-1]==2)&&(!isValidInstructionCall(arg1))\
           &&!isValidInstructionCall(arg2))
        {
            return code;
        }
        else
        {
            return false;
        }
    }
}
