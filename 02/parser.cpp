#include <string>
#include <functional>
#include "parser.h"

bool tokenIsNumber(const std::string& str) {
    std::size_t pos;
    pos = str.find_first_not_of("0123456789");
    return pos == std::string::npos;
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

    while(pos2 != std::string::npos) {
        pos1 = text.find_first_not_of(delim, pos2);
        if(pos1 == std::string::npos) {
            break;
        }
        pos2 = text.find_first_of(delim, pos1);
        token = text.substr(pos1, pos2 - pos1);
        if (tokenIsNumber(token)) {
            ptrDigitCB(token);   
        } else {
        ptrStringCB(token);
        }
    }
    
    ptrFinishCB();
}

