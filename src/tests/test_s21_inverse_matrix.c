#include "s21_tests.h"

START_TEST(inverse_1x1_positive_test) {
  matrix_t dataMatrix;
  int rows = 1;
  int columns = 1;
  matrix_t actual, expected;

  s21_create_matrix(rows, columns, &dataMatrix);
  s21_create_matrix(rows, columns, &expected);

  dataMatrix.matrix[0][0] = 4;

  expected.matrix[0][0] = 0.25;

  int codeError = s21_inverse_matrix(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);
  ck_assert_double_eq_tol(actual.matrix[0][0], expected.matrix[0][0], 1e-7);

  s21_remove_matrix(&dataMatrix);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_2x2_positive_test) {
  matrix_t dataMatrix;
  int rows = 2;
  int columns = 2;
  matrix_t actual, expected;

  s21_create_matrix(rows, columns, &dataMatrix);
  s21_create_matrix(rows, columns, &expected);

  dataMatrix.matrix[0][0] = 4;
  dataMatrix.matrix[0][1] = 7;
  dataMatrix.matrix[1][0] = 2;
  dataMatrix.matrix[1][1] = 6;

  expected.matrix[0][0] = 0.6;
  expected.matrix[0][1] = -0.7;
  expected.matrix[1][0] = -0.2;
  expected.matrix[1][1] = 0.4;

  int codeError = s21_inverse_matrix(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);
  for (int i = 0; i < dataMatrix.rows; i++) {
    for (int j = 0; j < dataMatrix.columns; j++) {
      ck_assert_double_eq_tol(actual.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&dataMatrix);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_3x3_positive_test) {
  matrix_t dataMatrix;
  int rows = 3;
  int columns = 3;
  matrix_t actual, expected;
  s21_create_matrix(rows, columns, &dataMatrix);
  s21_create_matrix(rows, columns, &expected);

  dataMatrix.matrix[0][0] = 2;
  dataMatrix.matrix[0][1] = 5;
  dataMatrix.matrix[0][2] = 7;
  dataMatrix.matrix[1][0] = 6;
  dataMatrix.matrix[1][1] = 3;
  dataMatrix.matrix[1][2] = 4;
  dataMatrix.matrix[2][0] = 5;
  dataMatrix.matrix[2][1] = -2;
  dataMatrix.matrix[2][2] = -3;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  int codeError = s21_inverse_matrix(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);
  for (int i = 0; i < dataMatrix.rows; i++) {
    for (int j = 0; j < dataMatrix.columns; j++) {
      ck_assert_double_eq_tol(actual.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&dataMatrix);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_matrix_CALC_ERROR_test) {
  matrix_t dataMatrix, actual;
  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1;
  dataMatrix.matrix[0][1] = 2;
  dataMatrix.matrix[0][2] = 3;
  dataMatrix.matrix[1][0] = 4;
  dataMatrix.matrix[1][1] = 5;
  dataMatrix.matrix[1][2] = 6;
  dataMatrix.matrix[2][0] = 7;
  dataMatrix.matrix[2][1] = 8;
  dataMatrix.matrix[2][2] = 9;

  int codeError = s21_inverse_matrix(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, CALC_ERROR);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(inverse_matrix_non_square_test) {
  matrix_t dataMatrix, actual;
  int rows = 2;
  int columns = 3;

  s21_create_matrix(rows, columns, &dataMatrix);

  int codeError = s21_inverse_matrix(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(inverse_null_matrix_test) {
  matrix_t *dataMatrix = NULL;
  matrix_t actual;

  int codeError = s21_inverse_matrix(dataMatrix, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

Suite *suiteInverseMatrix(void) {
  Suite *s = suite_create("suite_inverseMatrix");
  TCase *tc = tcase_create("tc_inverseMatrix");

  tcase_add_test(tc, inverse_1x1_positive_test);
  tcase_add_test(tc, inverse_2x2_positive_test);
  tcase_add_test(tc, inverse_3x3_positive_test);
  tcase_add_test(tc, inverse_matrix_CALC_ERROR_test);
  tcase_add_test(tc, inverse_matrix_non_square_test);
  tcase_add_test(tc, inverse_null_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}