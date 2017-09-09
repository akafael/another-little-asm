#ifndef YLA_LEXER_H_
#define YLA_LEXER_H_

#define DEBUG_LEXER 0

#include <string>
#include "languagedefinition.h"

using namespace std;

/**
 * Código para indentificar o tipo de token
 */
typedef enum{
// Tokens Inválidos ( Valores negativos )
    ERRCHAR     = -3, ///< Palavra mal formatada
    ERRNUM      = -2, ///< Número mal formatado
    INVALID     = -1,
// Simbolos Terminais:
    SPC         =  0, ///< Espaço em branco ' ' ou \t
    COMMA       =  1, // ,
    COLON       =  2, // :
    SEMICOLON   =  3, // ;
    PLUS        =  4, // +
    MINUS       =  5, // -
    LINE_END    =  6, // \n
    STR_END     =  7, // \0
// Simbolos não terminais:
    NUM_DEC     =  8,  ///< Número em decimal
    NUM_HEX     =  9,  ///< Número em hexadecimal
    WORD        =  10,
    LABEL       =  11,
    INSTR0      =  12,
    INSTR1      =  13,
    INSTR2      =  14,
    COMMENTARY  =  15
} TokenType;

/** Token identificado junto do conteúdo */
typedef struct{
    TokenType type;
    std::string string;
} token;

/** Instrução a ser executada com parâmetros */
typedef struct{
    InstructionCode opcode;
    token *args; ///< Vetor de parâmetros
} instructionLine;

/**
 * Verifica uma string em busca de tokens válidos
 * @param  line     String de Entrada
 * @param  position Posição
 * @return          token
 */
token scanner(std::string line, int *position);

#endif // YLA_PARSER_H_
