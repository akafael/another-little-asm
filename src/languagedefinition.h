/**
 * @file languagedefinition.h
 * #brief Definições da liguagem assembly
 *
 * @authors Rafael Lima
 */

#ifndef YLA_LANGUAGE_DEFINITION_H_
#define YLA_LANGUAGE_DEFINITION_H_

/**
 * Código das instruções
 */
 typedef enum {
    ADD      = 0,
    SUB      = 1,
    MULT     = 2,
    DIV      = 3,
    JMP      = 4,
    JMPN     = 5,
    JMPP     = 6,
    JMPZ     = 7,
    COPY     = 8,
    LOAD     = 9,
    STORE    = 10,
    INPUT    = 11,
    OUTPUT   = 12,
    STOP     = 13,
    SECTION  = 14,
    SPACE0   = 15,
    SPACE1   = 16,
    CONST    = 17,
    EQU      = 18,
    IF       = 19,
    MACRO    = 20,
    ENDMACRO = 21,
    BEGIN    = 22,
    END      = 23
} InstructionCode;

#define INSTRUCTIONS_NUMBER 24
#define INVALID_INSTRUCTION -1

const static char *InstrutionString[] = {
  "ADD",
  "SUB",
  "MULT",
  "DIV",
  "JMP",
  "JMPN",
  "JMPP",
  "JMPZ",
  "COPY",
  "LOAD",
  "STORE",
  "INPUT",
  "OUTPUT",
  "STOP",
  "SECTION",
  "SPACE",
  "SPACE",
  "CONST",
  "EQU",
  "IF",
  "MACRO",
  "ENDMACRO",
  "BEGIN",
  "END"
};

/**
 * Quantidade de argumentos de cada instrução
 * esta na mesma ordem do Instruction[]
 */
const static int InstructionArgNumber[] = {
    1, // "ADD"
    1, // "SUB"
    1, // "MULT"
    1, // "DIV"
    1, // "JMP"
    1, // "JMPN"
    1, // "JMPP"
    1, // "JMPZ"
    2, // "COPY"
    1, // "LOAD"
    1, // "STORE"
    1, // "INPUT"
    1, // "OUTPUT"
    0, // "STOP"
    1, // "SECTION"
    0, // "SPACE" sem parâmetros
    1, // "SPACE" com um parâmetro
    1, // "CONST"
    1, // "EQU"
    1, // "IF"
    0, // "MACRO"
    0, // "ENDMACRO"
    0, // "BEGIN"
    0  // "END"
};

/// @todo Separar Diretivas em um tipo diferente

#endif // YLA_LANGUAGE_DEFINITION_H_
