#ifndef YLA_LEXER_H_
#define YLA_LEXER_H_

#include <string>

using namespace std;

/**
 * Código para indentificar o tipo de token
 */
typedef enum{
    ERRCHAR     = -3, // Palavra mal formatada
    ERRNUM      = -2, // Número mal formatado
    INVALID     = -1,
    WORD        =  0, // Palavras
    NUM_DEC     =  1, // Número em decimal
    NUM_HEX     =  2, // Número em hexadecimal
    EMPTS       =  3, // Espaço em branco ' ' ou \t
    COMMA       =  4, // ,
    COLON       =  5, // :
    SEMICOLON   =  6, // ;
    PLUS        =  7, // +
    MINUS       =  8, // +
    LINE_END    =  9, // \n
    STR_END     =  10, // \0
    LABEL       =  11,
    INSTRUCTION =  12,
    SYMBOL      =  13,
    DIRECTIVE   =  14,
    COMMENTARY  =  15
} TokenType;

/**
 * Token identificado junto do conteúdo
 */
typedef struct{
    TokenType type;
    std::string string;
} token;

/**
 * Instrução a ser executada com parâmentros
 */
typedef struct{
    InstructionCode opcode;
    token *args; ///< Vetor de parâmetros
} instructionLine;

#define NEW_TOKEN(Tok,Toktype,tokstring) Tok.type = Toktype; Tok.string = Tokstring;

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna INVALID_INSTRUCTION
 *
 * @param  command String a ser Avaliada
 * @return         código da Instrução
 */
int isValidInstruction(std::string command);

#endif // YLA_PARSER_H_
