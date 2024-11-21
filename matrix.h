#include <vector>
#include <iostream>

template <typename T>
class MVector{
    
};

template <typename T>
class Matrix{
private:
    size_t m_rows;
    size_t m_cols;
    std::vector<std::vector<T>> m_elems;
public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(size_t size);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix(const std::vector<std::vector<T>>& other);
    ~Matrix();

    size_t getRows() const;
    size_t getCols() const;
    void printDims() const;
    std::vector<std::vector<T>> getElems() const;
    const T& getElem(size_t i, size_t j) const;

    Matrix getMinor(int row, int col) const;
    T determinant() const;
    Matrix calcComplements() const;
    Matrix transpose() const;
    Matrix inverse() const;

    Matrix<T>& operator=(const Matrix<T>& other);//копирующее присваивание
    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);
    Matrix<T>& operator*=(const Matrix<T>& other);
    Matrix<T>& operator*=(const T& other);
    Matrix<T>& operator/=(const T& other);
    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> operator*(const T& other) const;
    Matrix<T> operator/(const T& other) const;
    friend Matrix<T> operator*(const T& value, const Matrix<T>& matrix){
        return matrix * value;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix){
        for(auto& i: matrix.m_elems){
            for(auto& j: i){
                stream << j << " ";
            }
            stream << std::endl;
        }
        return stream;
    }
};

 

