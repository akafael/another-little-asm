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
 * @todo Alterar Opcodes para compatibilidade com simulador
 * @todo Separar Instruções de Diretivas em tipos distintos
 */
 typedef enum {
    ADD      = 1,
    SUB      = 2,
    MULT     = 3,
    DIV      = 4,
    JMP      = 5,
    JMPN     = 6,
    JMPP     = 7,
    JMPZ     = 8,
    COPY     = 9,
    LOAD     = 10,
    STORE    = 11,
    INPUT    = 12,
    OUTPUT   = 13,
    STOP     = 14,
    SECTION  = 15,
    SPACE0   = 16,
    SPACE1   = 17,
    CONST    = 18,
    EQU      = 19,
    IF       = 20,
    MACRO    = 21,
    ENDMACRO = 22,
    BEGIN    = 23,
    END      = 24
} InstructionCode;

#define INSTRUCTIONS_NUMBER 24
#define INVALID_INSTRUCTION 0

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
