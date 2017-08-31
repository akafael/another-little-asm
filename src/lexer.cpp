#include <vector>

#include "languagedefinition.h"
#include "lexer.h"

token scanner(std::string line, int *position){

    int i = *position;
    int j = 1;

    token tok;

    // Verifica Por Palavras
    if (isalpha(line.at(i)))
    {
        // Percorre Demais Posições até achar carcterer que não é letra
        for(j=1;i+j<line.size();j++){
            if(!(isalpha(line.at(i+j))||isdigit(line.at(i+j))||(line.at(i+j)=='_')))
                break;
        }

        // Cria token com a WORD achada
        tok.type = WORD;
        tok.string = line.substr(i,j);

    }
    else if(isdigit(line.at(i)))
    {

        // Verifica Se é Hexadecimal
        if((line.at(i)=='0')&&line.at(i+1)=='X'){
            // Percorre até achar o fim do número
            for(j=2;(i+j<line.size())&&(isxdigit(line.at(i+j)));j++);

            tok.type = NUM_HEX;
        }else{
            // Considera como valor Decimal
            for(j=1;(i+j<line.size())&&(isdigit(line.at(i+j)));j++);

            tok.type = NUM_DEC;
        }

        // Recorta String e acrescenta '\0'
        string linetokien = line.substr(i,j);
        std::vector<char> vtmp(linetokien.begin(),linetokien.end());
        vtmp.push_back('\0');

        // Prenche conteúdo do token com o valor achado
        tok.string = linetokien;
    }
    else
    {
        switch(line.at(i)){
        case ',' :
            tok.type = COMMA;
            tok.string = ',';
            break;
        case ':' :
            tok.type = COLON;
            tok.string = ':';
            break;
        case '+' :
            tok.type = PLUS;
            tok.string = '+';
            break;
        case '-' :
            tok.type = MINUS;
            tok.string = '-';
            break;
        case '\n' :
            tok.type = LINE_END;
            tok.string = '\n';
            break;
        case '\0' :
            tok.type = STR_END;
            tok.string = '\0';
            break;
        case ' ':
        case '\t':
            // Ignora Espaços em branco
            j++;
            break;
        default:
            // Caracter não reconhecido
            tok.type = ERRCHAR;
            tok.string = '!';
            break;
        }

    }

    // Muda Posição para o caracter depois do tokien analizado
    *position = i + j;

    // Retorna Token
    return tok;
}

int isValidInstruction(string command){
    for (int i = 0; i < INSTRUCTIONS_NUMBER; i++) {
        if (command.compare(InstrutionString[i]) == 0) {
            return i;
        }
    }
    return INVALID_INSTRUCTION;
}
