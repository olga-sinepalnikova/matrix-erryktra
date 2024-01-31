#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (is_matrix_incorrect(A) || is_matrix_incorrect(B)) return FAILURE;
  if (A->rows != B->rows || A->columns != B->columns) return FAILURE;

  for (int row_ind = 0; row_ind < A->rows; row_ind++) {
    for (int col_ind = 0; col_ind < A->columns; col_ind++) {
      if (fabs(A->matrix[row_ind][col_ind]) -
              fabs(B->matrix[row_ind][col_ind]) >
          EPS) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}