#include "check.h"
#include "s21_matrix.h"

START_TEST(create_normal) {
  matrix_t matrix = {0};
  int code = s21_create_matrix(3, 4, &matrix);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(matrix.columns, 4);
  ck_assert_int_eq(matrix.rows, 3);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      ck_assert_double_eq(matrix.matrix[i][j], 0.0);
    }
  }
  s21_remove_matrix(&matrix);
}

START_TEST(create_normal_2) {
  matrix_t matrix = {0};
  int rows = 1;
  int columns = 3;
  int code = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(matrix.columns, columns);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_double_eq(matrix.matrix[0][0], 0.0);
  ck_assert_double_eq(matrix.matrix[0][1], 0.0);
  ck_assert_double_eq(matrix.matrix[0][2], 0.0);
  s21_remove_matrix(&matrix);
}

START_TEST(create_incorrect) {
  int code = s21_create_matrix(3, 4, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}

START_TEST(create_incorrect_2) {
  matrix_t matrix = {0};
  int code = s21_create_matrix(-1, 4, &matrix);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}

START_TEST(create_incorrect_3) {
  matrix_t matrix = {0};
  int code = s21_create_matrix(3, -666, &matrix);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}

START_TEST(create_incorrect_4) {
  int code = s21_create_matrix(0, -666, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}

START_TEST(remove_normal) {
  matrix_t matr = {0};
  int code = s21_create_matrix(3, 3, &matr);

  if (code == OK) {
    for (int i = 0; i < matr.rows; i++) {
      for (int j = 0; j < matr.columns; j++) {
        matr.matrix[i][j] = 21;
      }
    }
    s21_remove_matrix(&matr);

    ck_assert_ptr_null(matr.matrix);
    ck_assert_int_eq(matr.rows, 0);
    ck_assert_int_eq(matr.columns, 0);
  }
}

START_TEST(remove_normal_2) {
  matrix_t matr = {0};
  int code = s21_create_matrix(10, 1, &matr);
  if (code == OK) {
    for (int i = 0; i < matr.rows; i++) {
      for (int j = 0; j < matr.columns; j++) {
        matr.matrix[i][j] = 21;
      }
    }
    s21_remove_matrix(&matr);

    ck_assert_ptr_null(matr.matrix);
    ck_assert_int_eq(matr.rows, 0);
    ck_assert_int_eq(matr.columns, 0);
  }
}

START_TEST(eq_matrix) {
  matrix_t matr = {0};
  int code_1 = s21_create_matrix(3, 3, &matr);
  if (code_1 == OK) fill_matrix(&matr, 21);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(3, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 21);

  if (code_1 == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, &matr2);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_2) {
  matrix_t matr = {0};
  int code_1 = s21_create_matrix(10, 3, &matr);
  if (code_1 == OK) fill_matrix(&matr, 654);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(10, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 654);

  if (code_1 == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, &matr2);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_3) {
  matrix_t matr = {0};
  int code = s21_create_matrix(10, 3, &matr);
  if (code == OK) fill_matrix(&matr, 654.000000008);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(10, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 654.000000008);

  if (code == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, &matr2);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_fail) {
  matrix_t matr = {0};
  int code = s21_create_matrix(1, 3, &matr);
  if (code == OK) fill_matrix(&matr, 654);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(10, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 654);

  if (code == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, &matr2);
    ck_assert_int_eq(result, FAILURE);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_fail_2) {
  matrix_t matr = {0};
  int code = s21_create_matrix(1, 3, &matr);
  if (code == OK) fill_matrix(&matr, 654);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(1, 5, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 654);

  if (code == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, &matr2);
    ck_assert_int_eq(result, FAILURE);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_fail_3) {
  matrix_t matr = {0};
  int code = s21_create_matrix(1, 3, &matr);
  if (code == OK) fill_matrix(&matr, 654);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(10, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 654);

  if (code == OK && code_2 == OK) {
    int result = s21_eq_matrix(NULL, &matr2);
    ck_assert_int_eq(result, FAILURE);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_fail_4) {
  matrix_t matr = {0};
  int code = s21_create_matrix(1, 3, &matr);
  if (code == OK) fill_matrix(&matr, 654);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(10, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 654);

  if (code == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, NULL);
    ck_assert_int_eq(result, FAILURE);
    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(eq_matrix_fail_5) {
  matrix_t matr = {0};
  int code = s21_create_matrix(10, 3, &matr);
  if (code == OK) fill_matrix(&matr, 666);

  matrix_t matr2 = {0};
  int code_2 = s21_create_matrix(10, 3, &matr2);
  if (code_2 == OK) fill_matrix(&matr2, 0);

  if (code == OK && code_2 == OK) {
    int result = s21_eq_matrix(&matr, &matr2);
    ck_assert_int_eq(result, FAILURE);

    s21_remove_matrix(&matr);
    s21_remove_matrix(&matr2);
  }
}

START_TEST(sum_normal) {
  matrix_t A = {0}, B = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(3, 3, &A);
  if (code_A == OK) fill_matrix(&A, 1);

  int code_B = s21_create_matrix(3, 3, &B);
  if (code_B == OK) fill_matrix(&B, 2);

  int code_exp = s21_create_matrix(3, 3, &expected);
  if (code_exp == OK) fill_matrix(&expected, 3);

  if (code_A == OK && code_B == OK && code_exp == OK) {
    s21_sum_matrix(&A, &B, &res);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(sum_normal_2) {
  matrix_t A = {0}, B = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(1, 2, &A);
  if (code_A == OK) {
    fill_matrix(&A, 1);
    A.matrix[0][0] = 0;
  }

  int code_B = s21_create_matrix(1, 2, &B);
  if (code_B == OK) fill_matrix(&B, 20);

  int code_exp = s21_create_matrix(1, 2, &expected);
  if (code_exp == OK) {
    fill_matrix(&expected, 21);
    expected.matrix[0][0] = 20;
  }

  if (code_A == OK && code_B == OK && code_exp == OK) {
    s21_sum_matrix(&A, &B, &res);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(sum_failure) {
  matrix_t A = {0}, B = {0}, res = {0};
  int code_A = s21_create_matrix(1, 2, &A);
  int code_B = s21_create_matrix(5, 2, &B);

  if (code_A == OK && code_B == OK) {
    int code = s21_sum_matrix(&A, &B, &res);
    ck_assert_int_eq(code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(sum_failure_2) {
  matrix_t A = {0}, B = {0}, res = {0};
  int code_A = s21_create_matrix(1, 2, &A);
  int code_B = s21_create_matrix(5, 2, &B);

  if (code_A == OK && code_B == OK) {
    int code = s21_sum_matrix(NULL, &B, &res);
    ck_assert_int_eq(code, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(sub_normal) {
  matrix_t A = {0}, B = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(1, 2, &A);
  int code_B = s21_create_matrix(1, 2, &B);
  int code_exp = s21_create_matrix(1, 2, &expected);

  if (code_A == OK && code_B == OK && code_exp == OK) {
    fill_matrix(&A, 10);
    fill_matrix(&B, 12);
    s21_sub_matrix(&A, &B, &res);

    fill_matrix(&expected, -2);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(sub_normal_2) {
  matrix_t A = {0}, B = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(10, 2, &A);
  int code_B = s21_create_matrix(10, 2, &B);
  int code_exp = s21_create_matrix(10, 2, &expected);

  if (code_A == OK && code_B == OK && code_exp == OK) {
    fill_matrix(&A, 999);
    fill_matrix(&B, 333);
    s21_sub_matrix(&A, &B, &res);

    fill_matrix(&expected, 666);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(sub_failure) {
  matrix_t A = {0}, B = {0}, res = {0};
  int code_A = s21_create_matrix(10, 2, &A);
  int code_B = s21_create_matrix(10, 2, &B);

  if (code_A == OK && code_B == OK) {
    fill_matrix(&A, 999);
    fill_matrix(&B, 333);
    int res_code = s21_sub_matrix(&A, NULL, &res);

    ck_assert_int_eq(res_code, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(sub_failure_2) {
  matrix_t A = {0}, B = {0}, res = {0};
  int code_A = s21_create_matrix(10, 2, &A);
  int code_B = s21_create_matrix(5, 2, &B);

  if (code_A == OK && code_B == OK) {
    fill_matrix(&A, 999);
    fill_matrix(&B, 333);
    int res_code = s21_sub_matrix(&A, &B, &res);

    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(sub_failure_3) {
  matrix_t A = {0}, B = {0}, res = {0};
  int code_A = s21_create_matrix(1, 2, &A);
  int code_B = s21_create_matrix(10, 2, &B);

  if (code_A == OK && code_B == OK) {
    fill_matrix(&A, 999);
    fill_matrix(&B, 333);
    int res_code = s21_sub_matrix(&A, &B, &res);

    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(mul_number_normal) {
  matrix_t A = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(10, 2, &A);
  int code_exp = s21_create_matrix(10, 2, &expected);

  if (code_A == OK && code_exp == OK) {
    fill_matrix(&A, 999);
    int res_code = s21_mult_number(&A, 0.0, &res);

    ck_assert_int_eq(res_code, OK);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(mul_number_normal_2) {
  matrix_t A = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(1, 2, &A);
  if (code_A == OK) {
    A.matrix[0][1] = 100.0;
    A.matrix[0][2] = 50.0;

    int res_code = s21_mult_number(&A, 0.5, &res);

    if (s21_create_matrix(1, 2, &expected) == OK) {
      expected.matrix[0][1] = 50.0;
      expected.matrix[0][2] = 25.0;

      ck_assert_int_eq(res_code, OK);
      ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}

START_TEST(mul_number_failure) {
  matrix_t A = {0}, res = {0};
  if (s21_create_matrix(1, 2, &A) == OK) {
    int res_code = s21_mult_number(&A, NAN, &res);
    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
  }
}

START_TEST(mul_number_failure_2) {
  matrix_t A = {0}, res = {0};
  if (s21_create_matrix(1, 2, &A) == OK) {
    int res_code = s21_mult_number(NULL, 0.5, &res);
    ck_assert_int_eq(res_code, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
  }
}

START_TEST(mul_matrix_normal) {
  matrix_t A = {0}, B = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(3, 2, &A);
  if (code_A == OK) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 4;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = 5;
    A.matrix[2][0] = 3;
    A.matrix[2][1] = 6;
  }

  int code_B = s21_create_matrix(2, 3, &B);
  if (code_B == OK) {
    B.matrix[0][0] = 1;
    B.matrix[0][1] = -1;
    B.matrix[0][2] = 1;
    B.matrix[1][0] = 2;
    B.matrix[1][1] = 3;
    B.matrix[1][2] = 4;
  }

  int code_exp = s21_create_matrix(3, 3, &expected);
  if (code_exp == OK) {
    expected.matrix[0][0] = 9;
    expected.matrix[0][1] = 11;
    expected.matrix[0][2] = 17;
    expected.matrix[1][0] = 12;
    expected.matrix[1][1] = 13;
    expected.matrix[1][2] = 22;
    expected.matrix[2][0] = 15;
    expected.matrix[2][1] = 15;
    expected.matrix[2][2] = 27;
  }

  if (code_A == OK && code_B == OK && code_exp == OK) {
    int res_code = s21_mult_matrix(&A, &B, &res);
    ck_assert_int_eq(res_code, OK);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(mul_matrix_normal_2) {
  matrix_t A = {0}, B = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(5, 2, &A);
  if (code_A == OK) fill_matrix(&A, 21);

  int code_B = s21_create_matrix(2, 2, &B);
  if (code_B == OK) {
    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[1][0] = 3;
    B.matrix[1][1] = 4;
  }

  int code_exp = s21_create_matrix(5, 2, &expected);
  if (code_exp == OK) {
    expected.matrix[0][0] = 84;
    expected.matrix[1][0] = 84;
    expected.matrix[2][0] = 84;
    expected.matrix[3][0] = 84;
    expected.matrix[4][0] = 84;
    expected.matrix[0][1] = 126;
    expected.matrix[1][1] = 126;
    expected.matrix[2][1] = 126;
    expected.matrix[3][1] = 126;
    expected.matrix[4][1] = 126;
  }

  if (code_A == OK && code_B == OK && code_exp == OK) {
    int res_code = s21_mult_matrix(&A, &B, &res);
    ck_assert_int_eq(res_code, OK);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(mul_matrix_failure) {
  matrix_t A = {0}, B = {0}, res = {0};
  if (s21_create_matrix(5, 2, &A) == OK) {
    if (s21_create_matrix(2, 2, &B) == OK) {
      int res_code = s21_mult_matrix(&A, NULL, &res);
      ck_assert_int_eq(res_code, INCORRECT_MATRIX);
      s21_remove_matrix(&A);
      s21_remove_matrix(&B);
    }
  }
}

START_TEST(mul_matrix_failure_2) {
  matrix_t A = {0}, B = {0}, res = {0};
  if (s21_create_matrix(5, 2, &A) == OK && s21_create_matrix(2, 2, &B) == OK) {
    int res_code = s21_mult_matrix(NULL, &B, &res);
    ck_assert_int_eq(res_code, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(mul_matrix_failure_3) {
  matrix_t A = {0}, B = {0}, res = {0};
  if (s21_create_matrix(5, 2, &A) == OK &&
      s21_create_matrix(20, 10, &B) == OK) {
    int res_code = s21_mult_matrix(&A, &B, &res);
    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(mul_matrix_failure_4) {
  matrix_t A = {0}, B = {0}, res = {0};
  if (s21_create_matrix(59, 2, &A) == OK &&
      s21_create_matrix(5, 10, &B) == OK) {
    int res_code = s21_mult_matrix(&A, &B, &res);

    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }
}

START_TEST(transpose_normal) {
  matrix_t A = {0}, res = {0}, expected = {0};
  if (s21_create_matrix(1, 2, &A) == OK) {
    A.matrix[0][0] = 100.0;
    A.matrix[0][1] = 50.0;

    int res_code = s21_transpose(&A, &res);

    if (s21_create_matrix(2, 1, &expected) == OK) {
      expected.matrix[0][0] = 100.0;
      expected.matrix[1][0] = 50.0;

      ck_assert_int_eq(res_code, OK);
      ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
      s21_remove_matrix(&A);
      s21_remove_matrix(&res);
      s21_remove_matrix(&expected);
    }
  }
}

START_TEST(transpose_normal_2) {
  matrix_t A = {0}, res = {0}, expected = {0};
  if (s21_create_matrix(2, 2, &A) == OK) {
    A.matrix[0][0] = 100.0;
    A.matrix[0][1] = 50.0;
    A.matrix[1][0] = 21;
    A.matrix[1][1] = 21;

    int res_code = s21_transpose(&A, &res);

    if (s21_create_matrix(2, 2, &expected) == OK) {
      expected.matrix[0][0] = 100.0;
      expected.matrix[1][0] = 50.0;
      expected.matrix[0][1] = 21;
      expected.matrix[1][1] = 21;

      ck_assert_int_eq(res_code, OK);
      ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
      s21_remove_matrix(&A);
      s21_remove_matrix(&res);
      s21_remove_matrix(&expected);
    }
  }
}

START_TEST(transpose_failure) {
  matrix_t A = {0}, res = {0};
  if (s21_create_matrix(1, 2, &A) == OK) {
    A.matrix[0][0] = 100.0;
    A.matrix[0][1] = 50.0;
    int res_code = s21_transpose(NULL, &res);
    ck_assert_int_eq(res_code, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
  }
}

START_TEST(complements_normal) {
  matrix_t A = {0}, res = {0}, expected = {0};
  if (s21_create_matrix(3, 3, &A) == OK) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;

    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 2;

    A.matrix[2][0] = 5;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = 1;

    int res_code = s21_calc_complements(&A, &res);

    if (s21_create_matrix(3, 3, &expected) == OK) {
      expected.matrix[0][0] = 0;
      expected.matrix[0][1] = 10;
      expected.matrix[0][2] = -20;

      expected.matrix[1][0] = 4;
      expected.matrix[1][1] = -14;
      expected.matrix[1][2] = 8;

      expected.matrix[2][0] = -8;
      expected.matrix[2][1] = -2;
      expected.matrix[2][2] = 4;

      ck_assert_int_eq(res_code, OK);
      ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
      s21_remove_matrix(&A);
      s21_remove_matrix(&res);
      s21_remove_matrix(&expected);
    }
  }
}

START_TEST(complements_failure_1) {
  matrix_t A = {0}, res = {0};
  if (s21_create_matrix(3, 3, &A) == OK) {
    int res_code = s21_calc_complements(NULL, &res);
    ck_assert_int_eq(res_code, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
  }
}

START_TEST(complements_failure_2) {
  matrix_t A = {0}, res = {0};
  if (s21_create_matrix(3, 1, &A) == OK) {
    int res_code = s21_calc_complements(&A, &res);
    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
  }
}

START_TEST(determinant_normal) {
  matrix_t A = {0};
  double res = 0.0;
  if (s21_create_matrix(3, 3, &A) == OK) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;

    A.matrix[1][0] = 4;
    A.matrix[1][1] = 5;
    A.matrix[1][2] = 6;

    A.matrix[2][0] = 7;
    A.matrix[2][1] = 8;
    A.matrix[2][2] = 9;

    int res_code = s21_determinant(&A, &res);
    ck_assert_int_eq(res_code, OK);
    ck_assert_double_eq(res, 0);
    s21_remove_matrix(&A);
  }
}

START_TEST(determinant_normal_2) {
  matrix_t A = {0};
  double res = 0.0;
  if (s21_create_matrix(1, 1, &A) == OK) {
    A.matrix[0][0] = 1;

    int res_code = s21_determinant(&A, &res);
    ck_assert_int_eq(res_code, OK);
    ck_assert_double_eq(res, 1);
    s21_remove_matrix(&A);
  }
}

START_TEST(determinant_failure) {
  matrix_t A = {0};
  double res = 0.0;
  if (s21_create_matrix(1, 4, &A) == OK) {
    int res_code = s21_determinant(&A, &res);
    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
  }
}

START_TEST(determinant_failure_2) {
  double res = 0.0;

  int res_code = s21_determinant(NULL, &res);
  ck_assert_int_eq(res_code, INCORRECT_MATRIX);
}

START_TEST(inverse_normal) {
  matrix_t A = {0}, res = {0}, expected = {0};
  int code_A = s21_create_matrix(3, 3, &A);
  if (code_A == OK) {
    A.matrix[0][0] = 2;
    A.matrix[0][1] = 5;
    A.matrix[0][2] = 7;

    A.matrix[1][0] = 6;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;

    A.matrix[2][0] = 5;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = -3;
  }

  int code_exp = s21_create_matrix(3, 3, &expected);
  if (code_exp == OK) {
    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
  }
  if (code_A == OK && code_exp == OK) {
    int res_code = s21_inverse_matrix(&A, &res);
    ck_assert_int_eq(res_code, OK);
    ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}

START_TEST(inverse_failure) {
  matrix_t A = {0}, res = {0};
  if (s21_create_matrix(3, 3, &A) == OK) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 1;
    A.matrix[0][2] = 1;

    A.matrix[1][0] = 1;
    A.matrix[1][1] = 1;
    A.matrix[1][2] = 1;

    A.matrix[2][0] = 1;
    A.matrix[2][1] = 1;
    A.matrix[2][2] = 1;

    int res_code = s21_inverse_matrix(&A, &res);
    ck_assert_int_eq(res_code, CALCULATION_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&res);
  }
}

int main(void) {
  Suite *s1 = suite_create("s21_matrix: ");
  TCase *tc1_1 = tcase_create("s21_matrix: ");
  SRunner *sr = srunner_create(s1);
  int not_failed;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, create_normal);
  tcase_add_test(tc1_1, create_normal_2);
  tcase_add_test(tc1_1, create_incorrect);
  tcase_add_test(tc1_1, create_incorrect_2);
  tcase_add_test(tc1_1, create_incorrect_3);
  tcase_add_test(tc1_1, create_incorrect_4);

  tcase_add_test(tc1_1, remove_normal);
  tcase_add_test(tc1_1, remove_normal_2);

  tcase_add_test(tc1_1, eq_matrix);
  tcase_add_test(tc1_1, eq_matrix_2);
  tcase_add_test(tc1_1, eq_matrix_3);
  tcase_add_test(tc1_1, eq_matrix_fail);
  tcase_add_test(tc1_1, eq_matrix_fail_2);
  tcase_add_test(tc1_1, eq_matrix_fail_3);
  tcase_add_test(tc1_1, eq_matrix_fail_4);
  tcase_add_test(tc1_1, eq_matrix_fail_5);

  tcase_add_test(tc1_1, sum_normal);
  tcase_add_test(tc1_1, sum_normal_2);
  tcase_add_test(tc1_1, sum_failure);
  tcase_add_test(tc1_1, sum_failure_2);

  tcase_add_test(tc1_1, sub_normal);
  tcase_add_test(tc1_1, sub_normal_2);
  tcase_add_test(tc1_1, sub_failure);
  tcase_add_test(tc1_1, sub_failure_2);
  tcase_add_test(tc1_1, sub_failure_3);

  tcase_add_test(tc1_1, mul_number_normal);
  tcase_add_test(tc1_1, mul_number_normal_2);
  tcase_add_test(tc1_1, mul_number_failure);
  tcase_add_test(tc1_1, mul_number_failure_2);

  tcase_add_test(tc1_1, mul_matrix_normal);
  tcase_add_test(tc1_1, mul_matrix_normal_2);
  tcase_add_test(tc1_1, mul_matrix_failure);
  tcase_add_test(tc1_1, mul_matrix_failure_2);
  tcase_add_test(tc1_1, mul_matrix_failure_3);
  tcase_add_test(tc1_1, mul_matrix_failure_4);

  tcase_add_test(tc1_1, transpose_normal);
  tcase_add_test(tc1_1, transpose_normal_2);
  tcase_add_test(tc1_1, transpose_failure);

  tcase_add_test(tc1_1, complements_normal);
  tcase_add_test(tc1_1, complements_failure_1);
  tcase_add_test(tc1_1, complements_failure_2);

  tcase_add_test(tc1_1, determinant_normal);
  tcase_add_test(tc1_1, determinant_normal_2);
  tcase_add_test(tc1_1, determinant_failure);
  tcase_add_test(tc1_1, determinant_failure_2);

  tcase_add_test(tc1_1, inverse_normal);
  tcase_add_test(tc1_1, inverse_failure);

  srunner_run_all(sr, CK_ENV);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed == 0 ? 0 : 1;
}