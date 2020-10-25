#include <iostream>
#include "parser.h"
#include <functional>
#include <vector>
#include <cassert>

void tokenTest(const std::string& text, const std::vector<int>& correct) {
    std::vector<int> res;
    
    VoidFunc write2 = [&res]() { res.push_back(2); };
    VoidFunc write3 = [&res]() { res.push_back(3); };
    StrFunc write0 = [&res](const std::string& str) { res.push_back(0); };
    StrFunc write1 = [&res](const std::string& str) { res.push_back(1); };

    TokenParser parser;
    parser.setStartCallback(write2);
    parser.setStringTokenCallback(write1);
    parser.setDigitTokenCallback(write0);
    parser.setFinishCallback(write3);
    parser.Parse(text);
    assert(res == correct);
}

void noCallbackTest() {
    int a = 0;
    VoidFunc fin = [&a]() { a = 1; };
    TokenParser parser;
    parser.setFinishCallback(fin);
    parser.Parse("random text 112 67    4fg 78@f");
    assert(a == 1);
}

int main() {
    std::cout << "Testing digit/string type identification" << std::endl;
    std::vector<int> correct = {2, 1, 0, 1, 1, 1, 0, 1, 0, 3};
    tokenTest("Hello 123 world th1s 1s_str1ng2345   678 22@-2 0012", correct);
    std::cout << "Testing default callbacks" << std::endl;
    noCallbackTest();
    std::cout << "Testing line containing only spaces" << std::endl;
    correct = {2, 3};
    tokenTest("      ", correct);
    std::cout << "Testing empty line" << std::endl;
    tokenTest("", correct);
    return 0;
}
