#include <cstddef>
#include <iostream>
#include <exception>
#include "matrix.h"

int constProxyMatrix::operator[](size_t j) const {
    if(j >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return values[chosenRow + j];
}

int& ProxyMatrix::operator[](size_t j) {
    if(j >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return values[chosenRow + j];
}

void Matrix::setValues(int* arr) {
    for(size_t i = 0; i < rows * cols; i++) {
        values[i] = arr[i];
    }
}
      
size_t Matrix::getRows() const {
    return rows;
}
        
size_t Matrix::getColumns() const {
    return cols;
}

void Matrix::operator=(const Matrix& other) {
    Matrix tmpMatr(other);
    rows = tmpMatr.rows;
    cols = tmpMatr.cols;
    if(values != nullptr) {
        delete[] values;
    }
    values = new int[rows * cols];
    for(size_t i = 0; i < rows * cols; i++) {
        values[i] = tmpMatr.values[i];
    }
}
        
bool Matrix::operator==(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols) {
        return false;
    }
    for(size_t i = 0; i < rows * cols; i++) {
        if(values[i] != other.values[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}
      
Matrix Matrix::operator+(const Matrix& other) const {
    if(rows != other.rows || cols != other.cols)  {
        throw std::out_of_range("Incompatible dimensions");
    }
    int arr[rows * cols];
    for(size_t i = 0; i < rows * cols; i++) {
        arr[i] = values[i] + other.values[i];
    }
    return Matrix(rows, cols, arr);
}
        
Matrix& Matrix::operator*=(int mult) {
    for(size_t i = 0; i < rows * cols; i++) {
        values[i] *= mult;
    }
    return *this;
}
        
void Matrix::printMatrix() const {
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            std::cout << values[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out, const Matrix& matr) {
    for(size_t i = 0; i < matr.rows; i++) {
        for(size_t j = 0; j < matr.cols; j++) {
            out << matr.values[i * matr.cols + j] << " ";
        }
        out << std::endl;
    }
    return out;
}
     
ProxyMatrix Matrix::operator[](size_t n) {
    if(n >= rows)  {
        throw std::out_of_range("Index out of range");
    }
    return ProxyMatrix(values, cols, n * cols);
}

constProxyMatrix Matrix::operator[](size_t n) const {
    if(n >= rows)  {
        throw std::out_of_range("Index out of range");
    }
    return constProxyMatrix(values, cols, n * cols);
}
