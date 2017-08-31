#ifndef YLA_PARSER_H_
#define YLA_PARSER_H_

#include <string>

using namespace std;

/**
 * Verifica se determinada String representa um comando válido
 * caso seja inválido retorna INVALID_INSTRUCTION
 *
 * @param  command String a ser Avaliada
 * @return         código da Instrução
 */
int isValidInstruction(std::string command);

#endif // YLA_PARSER_H_
