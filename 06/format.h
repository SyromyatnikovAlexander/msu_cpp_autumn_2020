#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <sstream>
#include <cstddef>
#include <stdexcept>

class IncorrectString : public std::logic_error {
    public:
        IncorrectString(const std::string& str) : std::logic_error(str) { }
};

class WrongArguments : public std::logic_error { 
    public:
        WrongArguments(const std::string& str) : std::logic_error(str) { }
};
    

class HelperFormat {
    std::string str;
    size_t counter = 0;
    
    public:        
        HelperFormat(const std::string& initial) : str(initial) { }
                
        template<class T>
        void substitute(const T& arg);
        
        template<class T, class... argsT>
        void substitute(const T& arg, const argsT&... args);
        
        std::string result() const {
            return str;
        }
};
    

template<class... argsT>
std::string format(const std::string& initial, const argsT&... args);

std::string format(const std::string& initial) {
    return initial;
}
 
#include "format_fromcpp.h"    
#endif
