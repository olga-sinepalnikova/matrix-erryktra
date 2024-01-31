#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (!is_matrix_incorrect(A)) {
    for (int row_ind = 0; row_ind < A->rows; row_ind++) {
      if (A->matrix[row_ind] != NULL) {
        free(A->matrix[row_ind]);
        A->matrix[row_ind] = NULL;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}