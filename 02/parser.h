#ifndef H_PARSER
#define H_PARSER

#include <functional>

using VoidFunc = std::function<void ()>;
using StrFunc = std::function<void (std::string& str)>;

bool tokenIsNumber(const std::string& str);

class TokenParser {
    VoidFunc ptrStartCB;
    VoidFunc ptrFinishCB;
    StrFunc ptrDigitCB;
    StrFunc ptrStringCB;
    
public:
    TokenParser() {
        ptrStartCB = []() { };
        ptrFinishCB = []() { };
        ptrDigitCB = [](const std::string& dig) { };
        ptrStringCB = [](const std::string& dig) { };
    }
    
    ~TokenParser() { }
    
    void setStartCallback(VoidFunc startCallback);
    void setDigitTokenCallback(StrFunc digitTokenCallback);
    void setStringTokenCallback(StrFunc stringTokenCallback);
    void setFinishCallback(VoidFunc finishCallback);
    void Parse(const std::string& filename);
};

#endif
