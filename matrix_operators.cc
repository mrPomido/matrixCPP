#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif
#include "specs.h"

template<typename T> 
size_t Matrix<T>::getRows() const{
    return m_rows;
}

template<typename T> 
size_t Matrix<T>::getCols() const{
    return m_cols;
}

template<typename T> 
std::vector<std::vector<T>> Matrix<T>::getElems() const{
    return m_elems;
}

template<typename T>
void Matrix<T>::printDims() const{
    std::cout << m_rows << " * " << m_cols << std::endl;
}

template<typename T>
const T& Matrix<T>::getElem(size_t i, size_t j) const{
    return m_elems[i][j];
}

template<typename T>
Matrix<T> Matrix<T>::getMinor(int row, int col) const{
    Matrix<T> minor(m_cols - 1, m_rows - 1);
    int minorRow = 0, minorCol = 0;
    for(int i = 0; i < m_rows; i++){
        if(i == row) continue;
        minorCol = 0;
        for(int j = 0; j < m_cols; j++){
            if(j == col) continue;
            minor.m_elems[minorRow][minorCol] = m_elems[i][j];
            minorCol += 1;
        }
        minorRow += 1;
    }
    return minor;
}

template<typename T>
T Matrix<T>::determinant() const{
    if(m_rows != m_cols){
        throw std::invalid_argument("The matrix is not square");
    }
    if(m_rows == 1){
        return m_elems[0][0];
    }
    else if(m_rows == 2){
        return m_elems[0][0] * m_elems[1][1] - m_elems[1][0] * m_elems[0][1];  
    }
    T det = 0.0;

    for(int j = 0; j < m_cols; j++){
        Matrix<T> submatrix = getMinor(0, j);
        det += ((j % 2 == 0) ? 1 : -1) * m_elems[0][j] * submatrix.determinant();
    }
    return det;
}

template<typename T>
Matrix<T> Matrix<T>::calcComplements() const{
    if(m_rows != m_cols) throw std::invalid_argument("The matrix is not square");
    Matrix<T> complements(m_rows, m_cols);
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            Matrix<T> minor = getMinor(i, j);
            T cofactor = (((j + i) % 2 == 0) ? 1 : -1) * minor.determinant();
            complements.m_elems[i][j] = cofactor;
        }
    }
    return complements;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> transposed(m_cols, m_rows);
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            transposed.m_elems[j][i] = m_elems[i][j];
        }
    }
    return transposed;
}

template<typename T>
Matrix<T> Matrix<T>::inverse() const{
    if(m_rows != m_cols) throw std::invalid_argument("The matrix is not square");
    return (this -> calcComplements()).transpose() / (this -> determinant());
}


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other){
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_elems = other.m_elems;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other){
    if(other.m_rows != m_rows || other.m_cols != m_cols){
        throw std::invalid_argument("The number of rows or columns does not match");
        return *this;
    }
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_elems[i][j] += other.m_elems[i][j];
        }
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other){
    if(other.m_rows != m_rows || other.m_cols != m_cols){
        throw std::invalid_argument("The number of rows or columns does not match");
        return *this;
    }
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_elems[i][j] -= other.m_elems[i][j];
        }
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& other){
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_elems[i][j] *= other;
        }
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other){
    if(m_cols != other.m_rows){
        throw std::invalid_argument("The number of rows and columns does not match");
        return *this;
    }
    Matrix<T> result(m_rows, other.m_cols);
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < other.m_cols; j++){
            for(size_t k = 0; k < m_cols; k++){
                result.m_elems[i][j] += m_elems[i][k] * other.m_elems[k][j];
            }
        }
    }
    *this = result;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& other){
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            m_elems[i][j] /= other;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const{
    if(other.m_rows != m_rows || other.m_cols != m_cols){
        throw std::invalid_argument("The number of rows or columns does not match");
    }
    Matrix<T> result(m_rows, m_cols);
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            result.m_elems[i][j] = m_elems[i][j] + other.m_elems[i][j];
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const{
    if(other.m_rows != m_rows || other.m_cols != m_cols){
        throw std::invalid_argument("The number of rows or columns does not match");
    }
    Matrix<T> result(m_rows, m_cols);
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            result.m_elems[i][j] = m_elems[i][j] - other.m_elems[i][j];
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const{
    if(m_cols != other.m_rows){
        throw std::invalid_argument("The number of rows and columns does not match");
        return *this;
    }
    Matrix<T> result(m_rows, other.m_cols);
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < other.m_cols; j++){
            for(size_t k = 0; k < m_cols; k++){
                result.m_elems[i][j] += m_elems[i][k] * other.m_elems[k][j];
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& other) const{
    Matrix<T> result(*this);
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            result.m_elems[i][j] *= other;
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& other) const{
    Matrix<T> result(*this);
    for(size_t i = 0; i < m_rows; i++){
        for(size_t j = 0; j < m_cols; j++){
            result.m_elems[i][j] /= other;
        }
    }
    return result;
}