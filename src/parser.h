#ifndef YLA_PARSER_H_
#define YLA_PARSER_H_

#include <string>

using namespace std;

/**
 * Define simbolos segundo a
 */
typedef enum{
    SYM_COMMENTARY = -1, ///< Não Simbolo
    SYM_TERM = 0,        ///< Simbolo Terminal
    SYM_DIRECTIVE = 1,    ///< Simbolo Não Terminal
    SYM_INSTRUCTION = 2, ///< Simbolo Não Terminal
    SYM_LABEL = 3,       ///< Simbolo Não Terminal
    SYM_NUM_DEC = 4,     ///< Simbolo Não Terminal
    SYM_NUM_HEX = 5          ///< Simbolo Não Terminal
} SymbolType;

typedef struct{
    string text;
    SymbolType type;
    int address;
} symbol;

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna INVALID_INSTRUCTION
 *
 * @param  command String a ser Avaliada
 * @return         código da Instrução
 */
int isValidInstruction(std::string command);

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna INVALID_DIRECTIVE
 *
 * @param  command String a ser Avaliada
 * @return         código da Diretiva
 */
int isValidDirective(string command);

#endif // YLA_PARSER_H_
