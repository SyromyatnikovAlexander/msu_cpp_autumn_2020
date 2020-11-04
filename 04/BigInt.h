#ifndef BIGINT_H
#define BIGINT_H


class BigInt{
    private:
        char* num = nullptr;
        size_t size; 
        bool positive = true;
    
        BigInt(size_t s, char* n = nullptr);
        BigInt tenTimes(size_t pow) const;
        BigInt part(size_t beg, size_t end) const; 
    
public:   

        BigInt(const std::string& str);
        BigInt(int number);        
        ~BigInt() { delete[] num; }
        
        BigInt(const BigInt& other);
        BigInt& operator=(const BigInt& other);
        BigInt(BigInt&& other);
        BigInt& operator=(BigInt&& other);
        friend std::ostream& operator<<(std::ostream& out, const BigInt& number);
        BigInt abs() const;
        BigInt operator+(const BigInt& other) const;
        BigInt operator+=(const BigInt& other);
        BigInt operator-() const;
        BigInt operator-(const BigInt& other) const;
        BigInt operator-(int other) const;
        friend BigInt operator-(int other, const BigInt& number);
        bool operator==(const BigInt& other) const;
        bool operator!=(const BigInt& other) const;
        bool operator>(const BigInt& other) const;
        bool operator>=(const BigInt& other) const;
        bool operator<(const BigInt& other) const;
        bool operator<=(const BigInt& other) const;
        BigInt operator+(int other) const;
        BigInt operator+=(int other);
        bool operator==(int other) const;
        bool operator>(int other) const;
        bool operator>=(int other) const;
        bool operator<(int other) const;
        bool operator<=(int other) const ;
        friend BigInt operator+(int intNum, const BigInt& bigNum) ;
        friend bool operator==(int intNum, const BigInt& bigNum);
        friend bool operator!=(int intNum, const BigInt& bigNum);
        friend bool operator>(int intNum, const BigInt& bigNum) ;
        friend bool operator>=(int intNum, const BigInt& bigNum);
        friend bool operator<(int intNum, const BigInt& bigNum);
        friend bool operator<=(int intNum, const BigInt& bigNum);
        BigInt operator*(const BigInt other) const;
        BigInt operator*(int other) const;
        friend BigInt operator*(int other, const BigInt& number);
        BigInt operator*=(const BigInt& other);
        BigInt operator*=(int other);
        
};

#endif
