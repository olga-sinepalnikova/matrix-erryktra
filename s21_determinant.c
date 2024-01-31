#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (is_matrix_incorrect(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  int code = OK;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    int sign = 1;
    *result = 0;
    matrix_t temp_matr = {0};
    for (int row = 0; row < A->rows && code == OK; row++) {
      double det = 0.0;
      code = get_minor(A, row, 0, &temp_matr);
      if (code == OK) {
        code = s21_determinant(&temp_matr, &det);
      }
      if (code == OK) {
        *result += sign * A->matrix[row][0] * det;
        sign *= -1;
      }
      s21_remove_matrix(&temp_matr);
    }
  }
  return code;
}