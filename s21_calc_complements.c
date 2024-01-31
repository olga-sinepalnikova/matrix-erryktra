#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_matrix_incorrect(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  int error_code = s21_create_matrix(A->rows, A->rows, result);
  if (error_code == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }

  double det = 0.0;
  matrix_t minor = {0};
  int code = OK;
  int sign = 1;
  for (int row_ind = 0; row_ind < A->rows && code == OK; row_ind++) {
    for (int col_ind = 0; col_ind < A->columns && code == OK; col_ind++) {
      code = get_minor(A, row_ind, col_ind, &minor);
      if (code == OK) {
        code = s21_determinant(&minor, &det);
        s21_remove_matrix(&minor);
      }
      if (code == OK) {
        result->matrix[row_ind][col_ind] = sign * det;
        sign *= -1;
      }
    }
  }
  return code;
}