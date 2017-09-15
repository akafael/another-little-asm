/**
 * @file msg_pt.h
 * @brief Mensagens do programa
 */

#ifndef YLA_MSGS_PT_H_
#define YLA_MSGS_PT_H_

#define MSG_ERR "\tERR 9000\n" // Mensagem Genérica usada para debug
#define MSG_ERR_ARGUMENT_NUMBER "\tNúmero de argumentos invalido\n\tSão necessarios 3 argumentos: o nome do fileName a ser compilado, a opcao e o nome do fileName objeto\n"
#define MSG_ERR_INVALID_ARGUMENT "\tO segundo argumento esta mal formado:\n\t -p: pre-processado\n\t -m: fileName apos a resolucao das macros\n\t -o: para o fileName objeto final\n"
#define MSG_ERR_FILE "\tProblemas ao abrir arquivo\n"
#define MSG_ERR_INVALID_INSTRUCTION "\tInstrução Inválida\n\e[0"
#define MSG_ERR_INVALID_TOKEN "\tToken Inválido.\n"

// Macros para Formatar Mensagens de ERR
#define PRINT_ERR(fileLine,MSG) cerr << "\n Linha " << \
                                          fileLine + 1 << ":\033[31m ERRO:" << \
                                          MSG << "\033[0m\n"

#define PRINT_ERR_TOKEN(fileLine,TOK) cerr << "\nLinha " << \
                                          fileLine + 1 << ":\033[31m ERRO LÉXICO: \033[0m\"" << \
                                          TOK << "\"\033[31m -> Token Inválido \033[0m\n"

#define PRINT_ERR_INSTRUCTION(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Instrução Inválida\033[0m\n"

#define PRINT_ERR_LABEL(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Rótulo Inválido\033[0m\n"

#define PRINT_ERR_ARG_NUM(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Número de argumentos Inválido.\033[0m\n"

#define PRINT_ERR_ARG(fileLine,INST,ARG) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Argumento \""<< ARG <<"\" Inválido\033[0m\n"

#endif // YLA_MSGS_PT_H_
