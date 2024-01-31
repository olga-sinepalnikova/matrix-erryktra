#include "s21_matrix.h"

// returns 0 - failure, 1 - ok
// fills all matrix with one number
int fill_matrix(matrix_t *A, double number) {
  if (A == NULL || isnan(number)) return 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = number;
    }
  }
  return 1;
}

// checks if matrix is incorrect;
// returns OK - 0; INCORRECT_MATRIX - 1;
int is_matrix_incorrect(matrix_t *A) {
  if (A == NULL) return INCORRECT_MATRIX;
  if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL)
    return INCORRECT_MATRIX;
  return OK;
}

int get_minor(matrix_t *A, int row, int column, matrix_t *res) {
  if (row >= A->rows || column >= A->columns) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, res) == INCORRECT_MATRIX)
    return INCORRECT_MATRIX;
  int new_row = 0, new_col = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0; j < A->columns; j++) {
      if (j == column) continue;
      res->matrix[new_row][new_col] = A->matrix[i][j];
      new_col++;
    }
    new_col = 0;
    new_row++;
  }
  return OK;
}

void initialize_matrix(matrix_t *A) {
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int sub_sum_handler(matrix_t *A, matrix_t *B, matrix_t *result, int is_sub) {
  if (is_matrix_incorrect(A) || is_matrix_incorrect(B)) return INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) == INCORRECT_MATRIX)
    return INCORRECT_MATRIX;

  for (int row_ind = 0; row_ind < A->rows; row_ind++) {
    for (int col_ind = 0; col_ind < A->columns; col_ind++) {
      if (is_sub) {
        result->matrix[row_ind][col_ind] =
            A->matrix[row_ind][col_ind] - B->matrix[row_ind][col_ind];
      } else {
        result->matrix[row_ind][col_ind] =
            A->matrix[row_ind][col_ind] + B->matrix[row_ind][col_ind];
      }
    }
  }
  return OK;
}