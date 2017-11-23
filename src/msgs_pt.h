/**
 * @file msg_pt.h
 * @brief Mensagens do programa
 */

#ifndef YLA_MSGS_PT_H_
#define YLA_MSGS_PT_H_

#define MSG_ERR "\tERR 9000\n" // Mensagem Genérica usada para debug
#define MSG_ERR_FILE "\tProblemas ao abrir arquivo\n"

#define MSG_ERR_LOADER_ARGUMENT_NUMBER "\tNúmero de argumentos inválido\n\tSão necessarios pelo menos 3 argumentos:\n o nome do fileName a ser compilado, a quantidade de chucks de mémoria seguida da posição inicial de cada um e dos tamanho.\n"
#define MSG_ERR_LOADER_ALLOCATION "\tOUT OF MEMORY - YOUR PROGRAM WILL NOT BE LOADED.\n"
#define MSG_ERR_ARGUMENT_NUMBER "\tNúmero de argumentos invalido\n\tSão necessarios 3 argumentos: o nome do fileName a ser compilado, a opcao e o nome do fileName objeto\n"
#define MSG_ERR_INVALID_ARGUMENT "\tO segundo argumento esta mal formado:\n\t -p: pre-processado\n\t -m: fileName apos a resolucao das macros\n\t -o: para o fileName objeto final\n"
#define MSG_ERR_INVALID_INSTRUCTION "\tInstrução Inválida\n\e[0"
#define MSG_ERR_INVALID_TOKEN "\tToken Inválido.\n"
#define MSG_ERR_LABEL_UNDEFINED "\033[31m  -> Rótulo Não definido\033[0m\n"
#define MSG_ERR_MISSING_SECTION_TEXT "Linha 1: \033[31m ERRO SINTÁTICO: -> Seção TEXT não declarada\033[0m\n"
#define MSG_ERR_ASSEMBLY "\t Erro Encontrado.\n"

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

#define PRINT_ERR_LABEL_UNDEFINIED(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Rótulo Não Definido\033[0m\n"

#define PRINT_ERR_LABEL_PUBLIC_EXTERN(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Rótulo Externo definido como público\033[0m\n"

#define PRINT_ERR_IF(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Uso Incorreto da diretiva IF\033[0m\n"

#define PRINT_ERR_LABEL_DUPLICATED(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Rótulo já definido\033[0m\n"

#define PRINT_ERR_INVALID_SECTION(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Definição de SECTION inválida, permitido somente TEXT ou DATA\033[0m\n"

#define PRINT_ERR_WRONG_SECTION_DATA_INSTRUCTION(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Diretiva na Seção Errada! Deveria estar na seção DATA.\033[0m\n"

#define PRINT_ERR_WRONG_SECTION_TEXT_INSTRUCTION(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SINTÁTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Instrução na Seção Errada! Deveria estar na seção TEXT.\033[0m\n"


#define PRINT_ERR_ARG_NUM(fileLine,INST) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Número de argumentos Inválido.\033[0m\n"

#define PRINT_ERR_ARG(fileLine,INST,ARG) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Argumento \033[0m\""<< ARG <<"\"\033[31m Inválido\033[0m\n"

#define PRINT_ERR_ARG_TYPE(fileLine,INST,ARG) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Argumento \033[0m\""<< ARG <<"\"\033[31m com tipo inválido\033[0m\n"

#define PRINT_ERR_ARG_TYPE_CONST(fileLine,INST,ARG) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Argumento \033[0m\""<< ARG <<"\"\033[31m com tipo inválido! Constante não é permitida como argumento de entrada.\033[0m\n"

#define PRINT_ERR_DIV0(fileLine,INST,ARG) cerr << "\nLinha " << \
    fileLine +1 << ":\033[31m ERRO ERRO SEMÂNTICO: \033[0m\""<< string(INST) <<\
    "\"\033[31m  -> Valor de \033[0m\""<< ARG <<"\"\033[31m Inválido. Dividindo Valor por zero!\033[0m\n"


#endif // YLA_MSGS_PT_H_
