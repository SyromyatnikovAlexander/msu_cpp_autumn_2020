#include <cstddef>
#include <iostream>
#include <exception>
#include "matrix.h"

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
      
size_t Matrix::getRows() {
    return rows;
}
        
size_t Matrix::getColumns() {
    return cols;
}
        
bool Matrix::operator==(const Matrix& other) {
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
      
Matrix Matrix::operator+(const Matrix& other) {
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
        
void Matrix::printMatrix() {
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            std::cout << values[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}
     
ProxyMatrix Matrix::operator[](size_t n) {
    if(n >= rows)  {
        throw std::out_of_range("Index out of range");
    }
    return ProxyMatrix(values, cols, n * cols);
}
