#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_matrix_incorrect(A) || is_matrix_incorrect(B)) return INCORRECT_MATRIX;
  if (A->columns != B->rows) return CALCULATION_ERROR;
  int error_code = s21_create_matrix(A->rows, B->columns, result);
  if (error_code == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }

  for (int row_ind = 0; row_ind < A->rows; row_ind++) {
    for (int col_ind = 0; col_ind < B->columns; col_ind++) {
      for (int b_row_ind = 0; b_row_ind < B->rows; b_row_ind++) {
        result->matrix[row_ind][col_ind] +=
            A->matrix[row_ind][b_row_ind] * B->matrix[b_row_ind][col_ind];
      }
    }
  }
  return OK;
}