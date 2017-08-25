/**
 * @file mensagens.h
 * @brief Mensagens do programa
 */

#ifndef MENSAGENS
#define MENSAGENS

#define MSG_ERRO_ARGUMENTOS "\tNumero de argumentos invalido\n\tSao necessarios 3 argumentos: o nome do arquivo a ser compilado, a opcao e o nome do arquivo objeto\n"
#define MSG_ERRO_SEGUNDO_ARGUMENTO "\tO segundo argumento esta mal formado:\n\t -p: pre-processado\n\t -m: arquivo apos a resolucao das macros\n\t -o: para o arquivo objeto final\n"
#define MSG_ERRO "\tErro 9000\n"
#define MSG_ERRO_ARQUIVO "\tProblemas ao abrir arquivo\n"
#define MSG_ERRO_INSTRUCAO_INVALIDA "\t Instrução Inválida\n"

// Macros para Formatar Mensagens de Erro
#define PRINT_ERRO(arquivo,linhaCode,MSG) cout << arquivo << ": Linha " << \
                                          linhaCode + 1 << ": erro:" << MSG
#define PRINT_ERRO_INSTRUCAO(linhaCode,INST)\
    cout << "Linha " << linhaCode +1 << " : "<< string(INST) <<" -> Instrução Inválida\n"

#endif
