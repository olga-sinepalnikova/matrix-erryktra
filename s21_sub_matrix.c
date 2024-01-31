#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = sub_sum_handler(A, B, result, 1);
  return code;
}