#ifndef MACROEVAL_H_
#define MACROEVAL_H_

#include <string>
#include <vector>

using namespace std;

typedef struct{
    string text;
    string content;
} labelMacro;

#define MACRO_NOT_FOUND -1

typedef enum{
    MACROEV_IGNORE_LINE = 0,
    MACROEV_READING_LINE = 1,
    MACROEV_WRITING_MACRO = 2,
} StateMacroEvaluation;

int macroeval(int argc, char ** argv);

int findMacroDefinition(vector<labelMacro> macroDefinitionTable,string macroText);

#endif
