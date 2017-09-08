#include "languagedefinition.h"
#include "parser.h"

int isValidInstruction(string command){
    for (int i = 0; i < INSTRUCTIONS_NUMBER; i++) {
        if (command.compare(InstrutionString[i]) == 0) {
            return i;
        }
    }
    return INVALID_INSTRUCTION;
}
