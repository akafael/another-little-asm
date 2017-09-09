#include "languagedefinition.h"
#include "parser.h"

int checkValidInstruction(string command){
    for (int i = 0; i < INSTRUCTIONS_NUMBER; i++) {
        if (command.compare(InstrutionString[i]) == 0) {
            return (i+1);
        }
    }
    return INVALID_INSTRUCTION;
}

int isValidInstruction(string command){
    for (int i = 0; i < INSTRUCTIONS_NUMBER; i++) {
        if (command.compare(InstrutionString[i]) == 0) {
            return (i+1);
        }
    }
    return false;
}

int isValidInstructionCall(string command, string arg1){
    int code = checkValidInstruction(command);

    if(code==INVALID_INSTRUCTION)
    {
        return false;
    }
    else
    {
        return((InstructionArgNumber[code]==1)&&!isValidInstruction(arg1));
    }
}

int isValidInstructionCall(string command, string arg1,string arg2){
    int code = checkValidInstruction(command);

    if(code==INVALID_INSTRUCTION)
    {
        return false;
    }
    else
    {
        return((InstructionArgNumber[code]==2)&&!isValidInstruction(arg1)&&!isValidInstruction(arg2));
    }
}
