#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

// Test the default constructor
TEST(S21MatrixConstructorTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
}

// Test the parametrized constructor
TEST(S21MatrixConstructorTest, ParametrizedConstructor) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 3);
}

// Test the copy constructor
TEST(S21MatrixConstructorTest, CopyConstructor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_THROW(S21Matrix matrixx(-1, -1), std::invalid_argument);

  S21Matrix copy(matrix);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 2);
  EXPECT_EQ(copy(0, 0), 1.0);
  EXPECT_EQ(copy(0, 1), 2.0);
  EXPECT_EQ(copy(1, 0), 3.0);
  EXPECT_EQ(copy(1, 1), 4.0);
}

// Test the move constructor
TEST(S21MatrixConstructorTest, MoveConstructor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix moved(std::move(matrix));
  EXPECT_EQ(moved.getRows(), 2);
  EXPECT_EQ(moved.getCols(), 2);
  EXPECT_EQ(moved(0, 0), 1.0);
  EXPECT_EQ(moved(0, 1), 2.0);
  EXPECT_EQ(moved(1, 0), 3.0);
  EXPECT_EQ(moved(1, 1), 4.0);
}

// Test the accessor and mutator methods
TEST(S21MatrixAccessorsMutatorsTest, AccessorsMutators) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 3);

  matrix.setRows(3);
  matrix.setCols(4);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
  EXPECT_THROW(matrix.setRows(-1), std::invalid_argument);
  EXPECT_THROW(matrix.setCols(-1), std::invalid_argument);
}

// Test matrix addition
TEST(S21MatrixOperationsTest, MatrixAddition) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 + matrix2;
  EXPECT_EQ(result(0, 0), 6.0);
  EXPECT_EQ(result(0, 1), 8.0);
  EXPECT_EQ(result(1, 0), 10.0);
  EXPECT_EQ(result(1, 1), 12.0);

  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 6.0);
  EXPECT_EQ(matrix1(0, 1), 8.0);
  EXPECT_EQ(matrix1(1, 0), 10.0);
  EXPECT_EQ(matrix1(1, 1), 12.0);

  matrix1 += matrix1;
  EXPECT_EQ(matrix1(0, 0), 12.0);
  EXPECT_EQ(matrix1(0, 1), 16.0);
  EXPECT_EQ(matrix1(1, 0), 20.0);
  EXPECT_EQ(matrix1(1, 1), 24.0);

  S21Matrix matrix3(2, 2);
  S21Matrix matrix4(3, 3);
  EXPECT_THROW(matrix3.SumMatrix(matrix4), std::invalid_argument);
  EXPECT_THROW(matrix3 += matrix4, std::invalid_argument);
  EXPECT_THROW(result = matrix3 + matrix4, std::invalid_argument);
}

// Test matrix subtraction
TEST(S21MatrixOperationsTest, MatrixSubtraction) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result(0, 0), -4.0);
  EXPECT_EQ(result(0, 1), -4.0);
  EXPECT_EQ(result(1, 0), -4.0);
  EXPECT_EQ(result(1, 1), -4.0);

  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), -4.0);
  EXPECT_EQ(matrix1(0, 1), -4.0);
  EXPECT_EQ(matrix1(1, 0), -4.0);
  EXPECT_EQ(matrix1(1, 1), -4.0);

  matrix1 -= matrix2;
  EXPECT_EQ(matrix1(0, 0), -9.0);
  EXPECT_EQ(matrix1(0, 1), -10.0);
  EXPECT_EQ(matrix1(1, 0), -11.0);
  EXPECT_EQ(matrix1(1, 1), -12.0);

  S21Matrix matrix3(2, 2);
  S21Matrix matrix4(3, 3);
  EXPECT_THROW(matrix3.SubMatrix(matrix4), std::invalid_argument);
  EXPECT_THROW(matrix3 -= matrix4, std::invalid_argument);
  EXPECT_THROW(result = matrix3 - matrix4, std::invalid_argument);
}

// Test matrix multiplication
TEST(S21MatrixOperationsTest, MatrixMultiplication) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix result = matrix1 * matrix2;
  EXPECT_EQ(result(0, 0), 58.0);
  EXPECT_EQ(result(0, 1), 64.0);
  EXPECT_EQ(result(1, 0), 139.0);
  EXPECT_EQ(result(1, 1), 154.0);

  matrix1.MulMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 58.0);
  EXPECT_EQ(matrix1(0, 1), 64.0);
  EXPECT_EQ(matrix1(1, 0), 139.0);
  EXPECT_EQ(matrix1(1, 1), 154.0);

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 1.0;
  matrix3(0, 1) = 2.0;
  matrix3(1, 0) = 4.0;
  matrix3(1, 1) = 5.0;

  S21Matrix matrix4(2, 2);
  matrix4(0, 0) = 7.0;
  matrix4(0, 1) = 8.0;
  matrix4(1, 0) = 9.0;
  matrix4(1, 1) = 10.0;

  matrix3 *= matrix4;

  EXPECT_EQ(matrix3(0, 0), 25.0);
  EXPECT_EQ(matrix3(0, 1), 28.0);
  EXPECT_EQ(matrix3(1, 0), 73.0);
  EXPECT_EQ(matrix3(1, 1), 82.0);

  S21Matrix matrix5(2, 2);
  S21Matrix matrix6(3, 3);
  EXPECT_THROW(matrix5.MulMatrix(matrix6), std::invalid_argument);
  EXPECT_THROW(result = matrix5 * matrix6, std::invalid_argument);
}

// Test scalar multiplication
TEST(S21MatrixOperationsTest, ScalarMultiplication) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double scalar = 2.0;

  S21Matrix result = matrix * scalar;
  EXPECT_EQ(result(0, 0), 2.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 6.0);
  EXPECT_EQ(result(1, 1), 8.0);

  S21Matrix result2 = scalar * matrix;
  EXPECT_EQ(result2(0, 0), 2.0);
  EXPECT_EQ(result2(0, 1), 4.0);
  EXPECT_EQ(result2(1, 0), 6.0);
  EXPECT_EQ(result2(1, 1), 8.0);

  matrix *= scalar;
  EXPECT_EQ(matrix(0, 0), 2.0);
  EXPECT_EQ(matrix(0, 1), 4.0);
  EXPECT_EQ(matrix(1, 0), 6.0);
  EXPECT_EQ(matrix(1, 1), 8.0);

  matrix.MulNumber(scalar);
  EXPECT_EQ(matrix(0, 0), 4.0);
  EXPECT_EQ(matrix(0, 1), 8.0);
  EXPECT_EQ(matrix(1, 0), 12.0);
  EXPECT_EQ(matrix(1, 1), 16.0);
}

// Test matrix transpose
TEST(S21MatrixOperationsTest, MatrixTranspose) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix result = matrix.Transpose();
  EXPECT_EQ(result.getRows(), 3);
  EXPECT_EQ(result.getCols(), 2);
  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(2, 1), 6.0);
}

// Test matrix complement calculation
TEST(S21MatrixOperationsTest, MatrixComplementCalculation) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_NO_THROW(matrix.CalcComplements());

  S21Matrix nonSquareMatrix(2, 3);
  EXPECT_THROW(nonSquareMatrix.CalcComplements(), std::invalid_argument);
}

// Test determinant calculation
TEST(S21MatrixOperationsTest, DeterminantCalculation) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_NO_THROW(matrix.Determinant());

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = -24.0;
  matrix2(1, 1) = 1.0;
  matrix2(1, 2) = -22.0;
  matrix2(2, 0) = 3.0;
  matrix2(2, 1) = -14.0;
  matrix2(2, 2) = 4.0;

  EXPECT_NO_THROW(matrix2.Determinant());

  S21Matrix nonSquareMatrix(2, 3);
  EXPECT_THROW(nonSquareMatrix.Determinant(), std::invalid_argument);
}

// Test matrix inversion
TEST(S21MatrixOperationsTest, MatrixInversion) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = -24.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = -22.0;
  matrix(2, 0) = 3.0;
  matrix(2, 1) = -14.0;
  matrix(2, 2) = 4.0;

  EXPECT_NO_THROW(matrix.InverseMatrix());

  matrix(0, 0) = 0;
  matrix(1, 1) = 0;
  matrix(2, 2) = 0;

  EXPECT_NO_THROW(matrix.InverseMatrix());

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 7.0;
  matrix1(0, 1) = 8.0;
  matrix1(1, 0) = 9.0;
  matrix1(1, 1) = 10.0;
  matrix1(2, 0) = 11.0;
  matrix1(2, 1) = 12.0;

  EXPECT_THROW(matrix1.InverseMatrix(), std::invalid_argument);

  S21Matrix singularMatrix(2, 2);
  singularMatrix(0, 0) = 0.0;
  singularMatrix(0, 1) = 0.0;
  singularMatrix(1, 0) = 0.0;
  singularMatrix(1, 1) = 0.0;

  EXPECT_THROW(singularMatrix.InverseMatrix(), std::invalid_argument);
}

// Test matrix equality
TEST(S21MatrixOperationsTest, MatrixEquality) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_EQ(matrix1, matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));

  matrix2(1, 1) = 5.0;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Test index access
TEST(S21MatrixOperationsTest, IndexAccess) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_EQ(matrix(0, 0), 1.0);
  EXPECT_EQ(matrix(0, 1), 2.0);
  EXPECT_EQ(matrix(1, 0), 3.0);
  EXPECT_EQ(matrix(1, 1), 4.0);

  // Test out-of-range access
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 2), std::out_of_range);
  EXPECT_THROW(matrix(2, 0), std::out_of_range);
  EXPECT_THROW(matrix(1, -1), std::out_of_range);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);

  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(3, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
  EXPECT_THROW(matrix(0, 3), std::out_of_range);

  EXPECT_NO_THROW(matrix(0, 0));
  EXPECT_NO_THROW(matrix(1, 1));

  double& value = matrix(0, 0);
  value = 10.0;
  EXPECT_EQ(matrix(0, 0), 10.0);
}

TEST(S21MatrixTest, AccessConstMatrix) {
  const S21Matrix matrix(2, 2);

  S21Matrix temp(2, 2);
  temp(0, 0) = 1.0;
  temp(0, 1) = 2.0;
  temp(1, 0) = 3.0;
  temp(1, 1) = 4.0;

  const S21Matrix constMatrix = temp;

  EXPECT_EQ(constMatrix(0, 0), 1.0);
  EXPECT_EQ(constMatrix(0, 1), 2.0);
  EXPECT_EQ(constMatrix(1, 0), 3.0);
  EXPECT_EQ(constMatrix(1, 1), 4.0);
  EXPECT_THROW(constMatrix(-1, -1), std::out_of_range);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}