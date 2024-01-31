#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_matrix_incorrect(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  double det = 0;
  int code = OK;
  code = s21_determinant(A, &det);
  if (fabs(det) < EPS) {
    code = CALCULATION_ERROR;
  }
  if (code == OK) {
    matrix_t temp = {0};
    code = s21_calc_complements(A, &temp);
    if (code == OK) {
      matrix_t transposed = {0};
      code = s21_transpose(&temp, &transposed);
      s21_remove_matrix(&temp);
      if (code == OK) {
        code = s21_mult_number(&transposed, 1 / det, result);
        s21_remove_matrix(&transposed);
      }
    }
  }
  if (code != OK) {
    s21_remove_matrix(result);
  }
  return code;
}