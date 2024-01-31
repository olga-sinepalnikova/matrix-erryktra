#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error_code = OK;
  if (rows < 1 || columns < 1 || result == NULL) return INCORRECT_MATRIX;
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix != NULL) {
    for (int row_ind = 0; row_ind < rows; row_ind++) {
      result->matrix[row_ind] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[row_ind] == NULL) {
        for (int i = 0; i < row_ind; i++) {
          free(result->matrix[row_ind]);
        }
        error_code = INCORRECT_MATRIX;
        break;
      }
    }
  } else {
    error_code = INCORRECT_MATRIX;
  }
  return error_code;
}