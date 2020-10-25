#include <string>
#include <functional>
#include "parser.h"
#include <locale>
#include <cstddef>

bool tokenIsNumber(const std::string& str) {
    std::size_t pos = 0;
    while(std::isdigit(str[pos]) && pos < str.length()) {
        pos++;
    }
    return pos >= str.length();
}

void TokenParser::setStartCallback(VoidFunc startCallback) {
    ptrStartCB = startCallback;
}

void TokenParser::setDigitTokenCallback(StrFunc digitTokenCallback) {
    ptrDigitCB = digitTokenCallback;
}
    
void TokenParser::setStringTokenCallback(StrFunc stringTokenCallback) {
    ptrStringCB = stringTokenCallback;
}
    
void TokenParser::setFinishCallback(VoidFunc finishCallback) {
    ptrFinishCB = finishCallback;
}
    
void TokenParser::Parse(const std::string& text) {
    ptrStartCB();
    
    std::string token;
    std::string delim = " \f\n\r\t\v";
    std::size_t pos1 = 0, pos2 = 0;
    
    while(pos2 < text.length()) {
        while(std::isspace(text[pos1]) && pos1 < text.length()) {
            pos1++;
        }
        if(pos1 >= text.length()) {
            break;
        }
        pos2 = pos1;
        while(!std::isspace(text[pos2]) && pos2 < text.length()) {
            pos2++;
        }
        token = text.substr(pos1, pos2 - pos1);
        if (tokenIsNumber(token)) {
            ptrDigitCB(token);   
        } else {
            ptrStringCB(token);
        }
        pos1 = pos2;
    }

    ptrFinishCB();
}
