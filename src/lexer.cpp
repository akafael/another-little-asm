#include <vector>

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

        // Cria token com a  achada
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

            if(i+j<line.size()&&isalpha(line.at(i+j))){
                tok.type = ERRNUM;
                j++; // Inclui caracter que causou o erro
                ///@todo Incluir todo o token até o primeiro separador
            }
            else
                tok.type = NUM_DEC;
        }

        // Prenche conteúdo do token com o valor achado
        tok.string = line.substr(i,j);;

    }
    else
    {
        // Armazena Caracter:
        tok.string = line.at(i);

        // Verifica tipos válidos
        switch(line.at(i)){
        case ',' :
            tok.type = COMMA;
            break;
        case ':' :
            tok.type = COLON;
            break;
        case '+' :
            tok.type = PLUS;
            break;
        case '-' :
            tok.type = MINUS;
            break;
        case '\n' :
            tok.type = LINE_END;
            break;
        case '\0' :
            tok.type = STR_END;
            break;
        case ' ':
        case '\t':
            // Associa ' ' a todo espaço em branco
            tok.type = SPC;
            tok.string = ' ';
            break;
        default:
            // Caracter não reconhecido
            tok.type = ERRCHAR;
            break;
        }
    }

    // Muda Posição para o caracter depois do tokien analizado
    *position = i + j - 1;

    // Retorna Token
    return tok;
}

vector<token> tokenizer(string line){
    vector<token> vtoks;
    for (int i=0; i<line.length(); ++i){
        // Identifica tokens e pula para o fim do token
        token tok = scanner(line,&i);
        if(tok.type!=SPC){
            vtoks.push_back(tok);
        }
    }
    return vtoks;
}
