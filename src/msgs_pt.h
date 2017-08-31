/**
 * @file msg_pt.h
 * @brief Mensagens do programa
 */

#ifndef YLA_MSGS_PT_H_
#define YLA_MSGS_PT_H_

#define MSG_ERR_ARGUMENT_NUMBER "\tNúmero de argumentos invalido\n\tSão necessarios 3 argumentos: o nome do fileName a ser compilado, a opcao e o nome do fileName objeto\n"
#define MSG_ERR_INVALID_ARGUMENT "\tO segundo argumento esta mal formado:\n\t -p: pre-processado\n\t -m: fileName apos a resolucao das macros\n\t -o: para o fileName objeto final\n"
#define MSG_ERR "\tERR 9000\n"
#define MSG_ERR_FILE "\tProblemas ao abrir fileName\n"
#define MSG_ERR_INVALID_INSTRUCTION "\t Instrução Inválida\n"

// Macros para Formatar Mensagens de ERR
#define PRINT_ERR(fileName,fileLine,MSG) cout << fileName << ": Linha " << \
                                          fileLine + 1 << ": ERR:" << MSG
#define PRINT_ERR_INSTRUCTION(fileLine,INST)\
    cout << "Linha " << fileLine +1 << " : "<< string(INST) <<" -> Instrução Inválida\n"

#endif // YLA_MSGS_PT_H_
