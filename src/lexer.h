#ifndef YLA_LEXER_H_
#define YLA_LEXER_H_

#include <string>
#include "languagedefinition.h"

using namespace std;

/**
 * Código para indentificar o tipo de token. Valores negativos
 * representam erros e valores positivos tokens válidos
 */
typedef enum{
    ERRCHAR     = -3, ///< Palavra mal formatada
    ERRNUM      = -2, ///< Número mal formatado
    INVALID     = -1,
    SPC         =  0, ///< Espaço em branco ' ' ou \t
    WORD        =  1, ///< Palavras
    NUM_DEC     =  2, ///< Número em decimal
    NUM_HEX     =  3, ///< Número em hexadecimal
    COMMA       =  4, // ,
    COLON       =  5, // :
    SEMICOLON   =  6, // ;
    PLUS        =  7, // +
    MINUS       =  8, // -
    LINE_END    =  9, // \n
    STR_END     =  10, // \0
    COMMENTARY  =  11
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
