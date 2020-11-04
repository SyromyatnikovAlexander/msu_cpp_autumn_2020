#ifndef H_MATRIX
#define H_MATRIX

class ProxyMatrix {
    protected:
        size_t chosenRow;
        size_t cols;
        int* values;
    public:
        ProxyMatrix(int* matrValues, int m, int i) {
            chosenRow = i;
            cols = m;
            values = matrValues;
        }
        int& operator[](size_t j);
        
};

class constProxyMatrix : public ProxyMatrix {
    public:
        constProxyMatrix(int* matrValues, int m, int i) : ProxyMatrix(matrValues, m, i) {}
        int operator[](size_t j) const;
};

class Matrix {
    private:
        size_t rows;
        size_t cols;
        int* values;
    public:
        Matrix(size_t n, size_t m) {
            rows = n;
            cols = m;
            values = new int[rows * cols];
        }
        
        Matrix(size_t n, size_t m, const int* arr) {
            rows = n;
            cols = m;
            values = new int[rows * cols];
            for(size_t i = 0; i < rows * cols; i++) {
                values[i] = arr[i];
            }
        }
        
        Matrix(const Matrix& original) {
            rows = original.rows;
            cols = original.cols;
            values = new int[rows * cols];
            for(size_t i = 0; i < rows * cols; i++) {
                values[i] = original.values[i];
            }
        }
        
        ~Matrix() {
            delete[] values;
        }
        
        
        
        void setValues(int* arr);
        size_t getRows() const;
        size_t getColumns() const;
        void operator=(const Matrix& other); 
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;
        Matrix operator+(const Matrix& other) const;
        Matrix& operator*=(int mult);
        ProxyMatrix operator[](size_t n);
        constProxyMatrix operator[](size_t n) const;
        void printMatrix() const;
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matr);

};

#endif
