#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_matrix_incorrect(A)) return INCORRECT_MATRIX;
  if (isnan(number)) return CALCULATION_ERROR;
  initialize_matrix(result);
  if (s21_create_matrix(A->rows, A->columns, result) == INCORRECT_MATRIX)
    return INCORRECT_MATRIX;
  for (int row_ind = 0; row_ind < A->rows; row_ind++) {
    for (int col_ind = 0; col_ind < A->columns; col_ind++) {
      result->matrix[row_ind][col_ind] = number * A->matrix[row_ind][col_ind];
    }
  }
  return OK;
}