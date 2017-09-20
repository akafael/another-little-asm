#ifndef YLA_PARSER_H_
#define YLA_PARSER_H_

#define DEBUG_PARSER 0

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * Define simbolos gramáticais
 */
typedef enum{
    SYM_COMMENTARY = -1, ///< Simbolo Ignorado
    SYM_TERM = 0,        ///< Simbolo Terminal
    SYM_DIRECTIVE = 1,   ///< Simbolo Não Terminal
    SYM_INSTRUCTION = 2, ///< Simbolo Não Terminal
    SYM_LABEL = 3,       ///< Simbolo Não Terminal
    SYM_NUM_DEC = 4,     ///< Simbolo Não Terminal
    SYM_NUM_HEX = 5,     ///< Simbolo Não Terminal
} SymbolType;

typedef enum{
    INVALID_ARG2        = -3,
    INVALID_ARG1        = -2,
    INVALID_ARG_NUMBER  = -1,
    INVALID_INSTRUCTION =  0
} InstructionErrorCode;

#define LABEL_NOT_FOUND -1

/**
 * Elemento da tabela de simbolos com referência as outras tabelas
 */
typedef struct{
    int content;
    SymbolType type;
    int address;
} symbol;

/**
 * Elemento da tabela de Instruções
 */
typedef struct{
    int code;
    int numArgs;
    string text;
} instruction;

/**
 * Elemento da tabela de rótulos
 */
typedef struct{
    int value;
    int addr;
    string text;
} label;

#define UNDEFINED_LABEL_ADDR -1

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna o código da instrução+1 se verdadeiro
 * ou zero se falso
 *
 * @param  command String a ser Avaliada
 * @return         código da Instrução ou código de erro (InstructionErrorCode)
 */
int isValidInstructionCall(string command);

/**
 * Verifica se as strings referentes a instrução e os parâmetros representam
 * uma chamada válida da função, isto é se o argumento não contém palavras
 * reservadas e se a instrução precisa de um argumento.
 *
 * @param  command Instrução
 * @param  arg1    Argumento
 * @return         código da Instrução ou código de erro (InstructionErrorCode)
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
 * @return         código da Instrução ou código de erro (InstructionErrorCode)
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

int findLabel(vector<label> labelTable,string labelText);

#endif // YLA_PARSER_H_
