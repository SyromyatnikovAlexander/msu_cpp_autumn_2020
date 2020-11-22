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

template<class T>
Error Serializer::save(T& object) {
    return object.serialize(*this);
}

template<class... argsT>
Error Serializer::operator()(argsT... args) {
    return Serializer::process(args...);
}

template<class T>
Error Serializer::process(T arg) {
    std::string tmpRes = toStr(arg);
    *out_ << tmpRes;
    return Error::NoError;
}

template<class T, class... argsT>
Error Serializer::process(T arg, argsT... args) {
    std::string tmpRes = toStr(arg);
    *out_ << tmpRes;
    *out_ << Separator;
    return Serializer::process(std::forward<argsT>(args)...);
}

template<class T>
Error Deserializer::load(T& object) {
    return object.deserialize(*this);
}
       
template<class... argsT>
Error Deserializer::operator()(argsT&... args) {
    return Deserializer::process(args...);
}

template<class T>
Error Deserializer::process(T& arg) {
    return Deserializer::processLoad(arg);
}

template<class T, class... argsT>
Error Deserializer::process(T& arg, argsT&... args) {
    Error tmpErr = processLoad(arg);
    if(tmpErr != Error::NoError) {
        return tmpErr;
    }
    return Deserializer::process(std::forward<argsT&>(args)...);
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
