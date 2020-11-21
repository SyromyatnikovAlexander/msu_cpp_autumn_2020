#ifndef SERIALIZER_FROMCPP_H
#define SERIALIZER_FROMCPP_H

std::string toStr(bool val) {
    std::string out = "";
    if(val) {
        out = "true";
    } else {
        out = "false";
    }
    return out;
}

std::string toStr(uint64_t val) {
    return std::to_string(val);
}

Serializer::Serializer(std::ostream& out) {
    out_ = &out;
}

Deserializer::Deserializer(std::istream& in) {
    in_ = &in;
}

Error Deserializer::processLoad(bool& value) {
    std::string text;
    *in_ >> text;
    if(text == "true") {
        value = true;
    } else if(text == "false") {
        value = false;
    } else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error Deserializer::processLoad(uint64_t& value) {
    std::string text;
    *in_ >> text;
    if(text == "") {
        return Error::CorruptedArchive;
    }
    value = 0;
    for(size_t i = 0; i < text.size(); i++) {
        if(!std::isdigit(text[i])) {
            return Error::CorruptedArchive;
        }
        value = value * 10 + (text[i] - '0');
    }
    return Error::NoError;
}


#endif
