/**
 * @file languagedefinition.h
 * #brief Definições da liguagem assembly
 *
 * @authors Rafael Lima
 */

#ifndef YLA_LANGUAGE_DEFINITION_H_
#define YLA_LANGUAGE_DEFINITION_H_

/**
 * Opcode das instruções
 */
 typedef enum {
    SPACE    = 0,
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
    CONST    = 16,
    EQU      = 17,
    IF       = 18,
    MACRO    = 19,
    ENDMACRO = 20,
    BEGIN = 21,
    END = 22
} InstructionCode;

#define INSTRUCTIONS_NUMBER 23
#define INVALID_INSTRUCTION -1

const static char *InstrutionString[] = {
  " ",
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
  "CONST",
  "EQU",
  "IF",
  "MACRO",
  "ENDMACRO",
  "BEGIN",
  "END"
};

 // esta na mesma ordem do Instruction[]
const static int InstructionArgNumber[] = {1,1,1,1,1,1,1,1,2,1,1,1,1,0,1,-1,1,1,1,0,0,0,0};

#endif // YLA_LANGUAGE_DEFINITION_H_
