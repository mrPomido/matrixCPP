#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif
#include "specs.h"

template <typename T>
Matrix<T>::Matrix() : m_rows(0), m_cols(0)  {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols){
    if(rows <= 0 || cols <= 0){
        throw std::invalid_argument("Matrix dimensions must be >= 0.");
    }
    // std::cout << "ELEMS CREATED FROM SCRATCH." << std::endl;
    m_elems = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
}

template <typename T>
Matrix<T>::Matrix(size_t size) : m_rows(size), m_cols(size){
    if(m_rows <= 0){
        throw std::invalid_argument("Matrix dimensions must be >= 0.");
    }
    // std::cout << "ELEMS CREATED FROM SCRATCH." << std::endl;
    m_elems = std::vector<std::vector<T>>(size, std::vector<T>(size));
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other): m_rows(other.m_rows), m_cols(other.m_cols), m_elems(other.m_elems){
    // std::cout << "ELEMS CREATED FROM&." << std::endl;
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) : m_rows(other.m_rows), m_cols(other.m_cols){
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_elems = std::move(other.m_elems);
    // std::cout << "ELEMS CREATED FROM&&." << std::endl;
}


template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& other) : m_rows(other.size()), m_cols(other[0].size()){
    size_t cols = other[0].size();
    for(auto& i : other){
        if(i.size() != cols) throw std::invalid_argument("Each row must have the same number of elements");
    }
    m_elems = other;
    // std::cout << "ELEMS CREATED FROM VECTOR(VECTOR)." << std::endl;
}

template <typename T>
Matrix<T>::~Matrix(){
    // std::cout << "ELEMS DELETED." << std::endl;
    // if(m_elems != nullptr) delete[] m_elems;
}