#include "s21_matrix_oop.h"

// Accessors

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

// Mutators

void S21Matrix::setRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("Numbers of rows must be posistive");
  }

  if (rows != rows_) {
    double** newMatrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
      newMatrix[i] = new double[cols_]{};
    }

    int minRows = std::min(rows, rows_);
    for (int i = 0; i < minRows; ++i) {
      std::memcpy(newMatrix[i], matrix_[i], cols_ * sizeof(double));
      delete[] matrix_[i];
    }

    delete[] matrix_;
    matrix_ = newMatrix;
    rows_ = rows;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument("Number of colums must be positive");
  }

  if (cols != cols_) {
    for (int i = 0; i < rows_; ++i) {
      double* newRow = new double[cols]{};
      std::memcpy(newRow, matrix_[i], std::min(cols, cols_) * sizeof(double));
      delete[] matrix_[i];
      matrix_[i] = newRow;
    }
    cols_ = cols;
  }
}

// Helpers
S21Matrix S21Matrix::GetMinor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minorRow = 0, minorCol = 0;

  for (int i = 0; i < rows_; ++i) {
    if (i == row) continue;

    minorCol = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == col) continue;

      minor.matrix_[minorRow][minorCol] = matrix_[i][j];
      ++minorCol;
    }

    ++minorRow;
  }

  return minor;
}

void S21Matrix::GaussJordanElimination(S21Matrix& identity) const {
  S21Matrix temp(*this);

  for (int i = 0; i < rows_; ++i) {
    if (temp.matrix_[i][i] == 0) {
      int k = i + 1;
      while (k < rows_ && temp.matrix_[k][i] == 0) {
        ++k;
      }

      if (k == rows_) {
        throw std::invalid_argument("Matrix is singular");
      }

      std::swap(temp.matrix_[i], temp.matrix_[k]);
      std::swap(identity.matrix_[i], identity.matrix_[k]);
    }

    double scale = temp.matrix_[i][i];
    for (int j = 0; j < cols_; ++j) {
      temp.matrix_[i][j] /= scale;
      identity.matrix_[i][j] /= scale;
    }

    for (int k = 0; k < rows_; ++k) {
      if (k == i) continue;

      double factor = temp.matrix_[k][i];
      for (int j = 0; j < cols_; ++j) {
        temp.matrix_[k][j] -= factor * temp.matrix_[i][j];
        identity.matrix_[k][j] -= factor * identity.matrix_[i][j];
      }
    }
  }
}