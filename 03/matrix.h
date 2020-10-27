#ifndef H_MATRIX
#define H_MATRIX

class ProxyMatrix {
    private:
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
        size_t getRows();
        size_t getColumns();
        bool operator==(const Matrix& other);
        Matrix operator+(const Matrix& other);
        Matrix& operator*=(int mult);
        ProxyMatrix operator[](size_t n) ;
        void printMatrix();

};

#endif
