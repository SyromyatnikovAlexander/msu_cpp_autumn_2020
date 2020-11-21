#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>
#include <cstdint>

enum class Error {
    NoError,
    CorruptedArchive
};

std::string toStr(bool val);
std::string toStr(uint64_t val);

class Serializer {
    private:
        static constexpr char Separator = ' ';
        std::ostream * out_;
        
    public:
        explicit Serializer(std::ostream& out);

        template<class T>
        Error save(T& object) {
            return object.serialize(*this);
        }

        template<class... argsT>
        Error operator()(argsT... args) {
            return Serializer::process(args...);
        }

    private:
        template<class T>
        Error process(T arg) {
            std::string tmpRes = toStr(arg);
            *out_ << tmpRes;
        return Error::NoError;
        }

        template<class T, class... argsT>
            Error process(T arg, argsT... args) {
            std::string tmpRes = toStr(arg);
            *out_ << tmpRes;
            *out_ << Separator;
            return Serializer::process(std::forward<argsT>(args)...);
        }
};

class Deserializer {
    private:
        std::istream *in_;
    
    public:
        explicit Deserializer(std::istream& in);

        template<class T>
        Error load(T& object) {
            return object.deserialize(*this);
        }
       
        template<class... argsT>
        Error operator()(argsT&... args) {
            return Deserializer::process(args...);
        }

    private:
        Error processLoad(bool& value);
        Error processLoad(uint64_t& value);

        template<class T>
        Error process(T& arg) {
            return Deserializer::processLoad(arg);
        }

        template<class T, class... argsT>
        Error process(T& arg, argsT&... args) {
            Error tmpErr = processLoad(arg);
            if(tmpErr != Error::NoError) {
                return tmpErr;
            }
            return Deserializer::process(std::forward<argsT&>(args)...);
        }
};

#include "serializer_fromcpp.h"
#endif
