#ifndef FORMAT_FROMCPP_H
#define FORMAT_FROMCPP_H

               
template<class T>
void HelperFormat::substitute(const T& arg) {
    std::string place = "{" + std::to_string(counter) + "}";
    size_t pos = 0;
    std::stringstream tmp;
            
    pos = str.find(place);
    if(pos == std::string::npos) {
        throw IncorrectString("Nowhere to substitute argument");
    }
    tmp << arg;            
    while(pos != std::string::npos) {
        str.replace(pos, place.size(), tmp.str());
        pos = str.find(place);
    }
    
    place =  "{" + std::to_string(counter + 1) + "}";
    pos = str.find(place);
    if(pos != std::string::npos) {
        throw WrongArguments("Too few arguments");
    }
    
    place = "{";
    pos = str.find(place);
    if(pos != std::string::npos) {
        throw IncorrectString("Incorrect string format");
    }
    place = "}";
    pos = str.find(place);
    if(pos != std::string::npos) {
       throw IncorrectString("Incorrect string format");
    }
}
        
template<class T, class... argsT>
void HelperFormat::substitute(const T& arg, const argsT&... args) {
    std::string place = "{" + std::to_string(counter) + "}";
    size_t pos = 0;
    std::stringstream tmp;
    pos = str.find(place);
    if(pos == std::string::npos) {
        throw IncorrectString("Nowhere to substitute argument");
    }
    tmp << arg;
    while(pos != std::string::npos) {                
        str.replace(pos, place.size(), tmp.str());
        pos = str.find(place);
    }
    counter++;
    substitute(args...);
}

template<class... argsT>
std::string format(const std::string& initial, const argsT&... args) {
    HelperFormat helper(initial);
    helper.substitute(args...);
    return helper.result();
}

#endif
