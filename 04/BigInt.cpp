#include <iostream>
#include <cstddef>
#include <string>
#include <algorithm>
#include "BigInt.h"

BigInt::BigInt(size_t s, char* n) {
    num = n;
    size = s;
    positive = true;
}
     

BigInt::BigInt(const std::string& str) {
    size_t i = 0;
    if(str[0] == '-') {
        positive = false;
        i++;
    }
    while(str[i] == '0' && i < str.size()) {
        i++;
    }
    size_t beg = i;
    size = str.size() - beg;
    num = new char[size * sizeof(char)];
    for(i = 0; i < size; i++) {
        num[i] = str[i + beg];
    }
}

BigInt::BigInt(int number) {
    if(number == 0) {
        size = 0;
        num = nullptr;
        return;
    }
    if(number < 0) {
        positive = false;
        number = -number;
    }
    std::string tmpStr = std::to_string(number);
    size = tmpStr.size();
    num = new char[size * sizeof(char)];
    for(size_t i = 0; i < size; i++) {
        num[i] = tmpStr[i];
    }
}


BigInt::BigInt(const BigInt& other) : size(other.size)
{
    positive = other.positive;
    num = new char[size * sizeof(char)];
    for(size_t i = 0; i < size; i++) {
        num[i] = other.num[i];
    }     
}

BigInt& BigInt::operator=(const BigInt& other) {
    if(this == &other) {
        return *this;
    }
    size = other.size;
    positive = other.positive;
    char* tmp = new char[size * sizeof(char)];
    delete[] num;
    num = tmp;
    for(size_t i = 0; i < size; i++) {
        num[i] = other.num[i];
    }
    return *this;
}

BigInt::BigInt(BigInt&& other) {
    size = other.size;
    positive = other.positive;
    num = other.num;
    other.num = nullptr;
    other.size = 0;
}

BigInt& BigInt::operator=(BigInt&& other) {
    if(this == &other) {
        return *this;
    }
    delete[] num;
    size = other.size;
    positive = other.positive;
    num = other.num;
    other.num = nullptr;
    other.size = 0;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInt& number) {
    if(number.size == 0) {
        out << '0';
        return out;
    }
    if(!number.positive) {
        out << '-';
    }
    for(size_t i = 0; i < number.size ; i++) {
        out << number.num[i];
    }
    
    return out;
}

BigInt BigInt::abs() const {
    if((*this).positive) {
        return *this;
    } else {
        return -(*this);
    }
}

BigInt BigInt::operator+(const BigInt& other) const {
    if(size == 0) {
        return other;
    }
    if(other.size == 0) {
        return *this;
    }
    size_t maxSize = std::max(size, other.size);
    size_t minSize = std::min(size, other.size);
    char* maxNum, * minNum;
    bool resPos = true;
    std::string resNum = "";
    int addDig = 0;
    if(positive == other.positive) {
        if(size > other.size) {
            maxNum = num;
            minNum = other.num;
        } else {
            maxNum = other.num;
            minNum = num;
        }
        resPos = positive;
        for(size_t i = 0; i < minSize; i++) {
            resNum.push_back(((maxNum[maxSize - 1 - i] - '0') + (minNum[minSize - 1 - i] - '0') + addDig) % 10 + '0');
            addDig = ((maxNum[maxSize - 1 - i] - '0') + (minNum[minSize - 1 - i] - '0') + addDig) / 10; 
        }
        for(size_t i = minSize; i < maxSize; i++) {
            resNum.push_back(((maxNum[maxSize - 1 - i] - '0') + addDig) % 10 + '0');
            addDig = ((maxNum[maxSize - 1 - i] - '0') + addDig) / 10;
        } 
        if(addDig > 0) {
            resNum.push_back('1');
        }
    } else {
        if((*this).abs() > other.abs()) {
            maxNum = num;
            minNum = other.num;
            resPos = (*this).positive;
        } else {
            maxNum = other.num;
            minNum = num;
            resPos = other.positive;
        }
        for(size_t i = 0; i < minSize; i++) {
            if(maxNum[maxSize - 1 - i] + addDig < minNum[minSize - 1 - i]) { 
                resNum.push_back(maxNum[maxSize - 1 - i] + addDig - minNum[minSize - 1 - i] + 10 + '0');
                addDig = -1;              
            } else {
                resNum.push_back(maxNum[maxSize - 1 - i] + addDig - minNum[minSize - 1 - i] + '0');
                addDig = 0;                
            }
        }
        for(size_t i = minSize; i < maxSize; i++) {
            if(maxNum[maxSize - 1 - i] + addDig < 0) {
                resNum.push_back(maxNum[maxSize - 1 - i] + addDig + 10);
                addDig = -1;                
            } else {
                resNum.push_back(maxNum[maxSize - 1 - i] + addDig);
                addDig = 0;
            }
        }
    }
    if(!resPos) {
        resNum.push_back('-');
    }
    std::reverse(resNum.begin(), resNum.end());
    return BigInt(resNum);
}

BigInt BigInt::operator+=(const BigInt& other) {
    *this = (*this + other);
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.positive = !tmp.positive;
    return tmp;
}

bool BigInt::operator==(const BigInt& other) const {
    if(size == 0 && other.size == 0) {
        return true;
    }
    if(positive != other.positive || size != other.size) {
        return false;
    }
    for(size_t i = 0; i < size; i++) {
        if(num[i] != other.num[i]) {
            return false;
        }
    }
    return true;
}   

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    if(size == 0 && other.size == 0) {
        return false;
    }
    if(positive && !other.positive) {
        return true;
    }
    if(!positive && other.positive) {
        return false;
    }
    if(!positive && !other.positive) {
        return -other > -(*this);
    }
    if(size > other.size) {
        return true;
    }
    if(size < other.size) {
        return false;
    }
    for(size_t i = 0; i < size; i++) {
        if(num[i] > other.num[i]) {
            return true;
        } 
        if(num[i] < other.num[i]) {
            return false;
        }
    }
    return false;
}

bool BigInt::operator>=(const BigInt& other) const {
    return (*this > other) || (*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    return !(*this >= other);
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

BigInt BigInt::operator+(int other) const {
    BigInt tmpOther(other);
    return *this + tmpOther;
}

BigInt BigInt::operator+=(int other) {
    BigInt tmpOther(other);
    *this = (*this + tmpOther);
    return *this;
}

bool BigInt::operator==(int other) const {
    BigInt tmpOther(other);
    return *this == tmpOther;
}

bool BigInt::operator>(int other) const {
    BigInt tmpOther(other);
    return *this > tmpOther;
}

bool BigInt::operator>=(int other) const {
    BigInt tmpOther(other);
    return *this >= tmpOther;
}

bool BigInt::operator<(int other) const {
    BigInt tmpOther(other);
    return *this < tmpOther;
}

bool BigInt::operator<=(int other) const {
    BigInt tmpOther(other);
    return *this <= tmpOther;
}

BigInt operator+(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return bigNum + other;
}

bool operator==(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return bigNum == other;
}

bool operator!=(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return other != bigNum;
}

bool operator>(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return other > bigNum;
}

bool operator>=(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return other >= bigNum;
}

bool operator<(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return other < bigNum;
}

bool operator<=(int intNum, const BigInt& bigNum) {
    BigInt other(intNum);
    return other <= bigNum;
}

BigInt BigInt::tenTimes(size_t pow) const {
    if(size == 0) {
        return *this;
    }
    char* newNum = new char[(size + pow) * sizeof(char)];
    for(size_t i = 0; i < size; i++) {
        newNum[i] = num[i];
    }
    for(size_t i = size; i < size + pow; i++) {
        newNum[i] = '0';
    }
    return BigInt(size + pow, newNum);
}

BigInt BigInt::part(size_t beg, size_t end) const {
    if(size <= beg) {
        return BigInt(0, nullptr);
    }
    size_t newEnd = std::min(size, end);
    size_t newSize = newEnd - beg;
    char* resNum = new char[(newSize) * sizeof(char)];
    for(size_t i = 0; i < newSize; i++) {
        resNum[newSize - i - 1] = num[size - beg - i - 1];
    }
    return BigInt(newEnd - beg, resNum);
}

BigInt BigInt::operator*(const BigInt other) const {
    if(size == 0 || other.size == 0) {
        return BigInt(0, nullptr);     
    }
    bool resPos = (positive == other.positive);
    size_t maxSize = std::max(size, other.size);
    if(maxSize == 1) {
        int tmp = (num[0] - '0') * (other.num[0] - '0');
        std::string resNum = "";
        if(tmp >= 10) {
            resNum.push_back(tmp / 10 + '0');
        }
        resNum.push_back(tmp % 10 + '0');
        return BigInt(resNum);
    }
    
    BigInt first1 = (*this).part(0, maxSize / 2);
    BigInt first2 = other.part(0, maxSize / 2);
    BigInt last1 = (*this).part(maxSize / 2, maxSize);
    BigInt last2 = other.part(maxSize / 2, maxSize);
    BigInt karF = first1 * first2;
    BigInt karL = last1 * last2;
    BigInt karM = ((first1 + last1) * (first2 + last2)) + ((-karF) + (-karL));
    BigInt res = karL.tenTimes((maxSize / 2) * 2) + karM.tenTimes(maxSize / 2) + karF;
    res.positive = resPos;
    return res;
}

BigInt BigInt::operator*(int other) const {
    BigInt tmpNum(other);
    return (*this) * tmpNum;
}

BigInt operator*(int other, const BigInt& number) {
    BigInt tmpNum(other);
    return tmpNum * number;
}

BigInt BigInt::operator*=(const BigInt& other) { 
    *this = (*this * other);
    return *this;
}

BigInt BigInt::operator*=(int other) {
    BigInt tmpOther(other);
    *this = ((*this) * tmpOther);
    return *this;
}

BigInt BigInt::operator-(const BigInt& other) const {
    return (*this) + (-other);
}

BigInt BigInt::operator-(int other) const {
    BigInt tmpNum(other);
    return (*this) - tmpNum;
}

BigInt operator-(int other, const BigInt& number) {
    BigInt tmpNum(other);
    return tmpNum - number;
}


