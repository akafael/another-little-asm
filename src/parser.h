#ifndef YLA_PARSER_H_
#define YLA_PARSER_H_

#define DEBUG_PARSER 0

#include <string>

using namespace std;

/**
 * Define simbolos segundo a
 */
typedef enum{
    SYM_COMMENTARY = -1, ///< Não Sim
    SYM_TERM = 0,        ///< Simbolo Terminal
    SYM_DIRECTIVE = 1,   ///< Simbolo Não Terminal
    SYM_INSTRUCTION = 2, ///< Simbolo Não Terminal
    SYM_LABEL = 3,       ///< Simbolo Não Terminal
    SYM_NUM_DEC = 4,     ///< Simbolo Não Terminal
    SYM_NUM_HEX = 5,     ///< Simbolo Não Terminal
} SymbolType;

typedef struct{
    void *content;
    SymbolType type;
    int address;
} symbol;

typedef struct{
    int code;
    int numArgs;
    string text;
} instruction;

typedef struct{
    int value;
    int addr;
    string text;
} label;

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna INVALID_INSTRUCTION
 *
 * @param  command String a ser Avaliada
 * @return         código da Instrução
 */
int checkValidInstruction(string command);

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna o código da instrução+1 se verdadeiro
 * ou zero se falso
 *
 * @param  command String a ser Avaliada
 * @return         código da Instrução
 */
int isValidInstruction(string command);

/**
 * Verifica se as strings referentes a instrução e os parâmetros representam
 * uma chamada válida da função, isto é se o argumento não contém palavras
 * reservadas e se a instrução precisa de um argumento.
 *
 * @param  command Instrução
 * @param  arg1    Argumento
 * @return         Verdadeiro ou falso;
 */
int isValidInstructionCall(string command, string arg1);

/**
 * Verifica se as strings referentes a instrução e os parâmetros representam
 * uma chamada válida da função, isto é se os argumentos não contém palavras
 * reservadas e se a instrução precisa de dois argumento.
 *
 * @param  command Instrução
 * @param  arg1    Argumento
 * @param  arg2    Argumento
 * @return         Verdadeiro ou falso;
 */
int isValidInstructionCall(string command, string arg1,string arg2);

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna INVALID_DIRECTIVE
 *
 * @param  command String a ser Avaliada
 * @return         código da Diretiva
 */
int isValidDirective(string command);

#endif // YLA_PARSER_H_
