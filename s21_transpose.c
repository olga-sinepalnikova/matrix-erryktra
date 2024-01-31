#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (is_matrix_incorrect(A)) return INCORRECT_MATRIX;
  int error_code = s21_create_matrix(A->columns, A->rows, result);
  if (error_code == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }

  for (int row_ind = 0; row_ind < A->rows; row_ind++) {
    for (int col_ind = 0; col_ind < A->columns; col_ind++) {
      result->matrix[col_ind][row_ind] = A->matrix[row_ind][col_ind];
    }
  }
  return OK;
}