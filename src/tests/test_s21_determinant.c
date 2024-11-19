#include "s21_tests.h"

START_TEST(determinant_1x1_positive_test) {
  matrix_t dataMatrix;
  int rows = 1;
  int columns = 1;
  double actual;

  s21_create_matrix(rows, columns, &dataMatrix);
  dataMatrix.matrix[0][0] = 5.0;

  int codeError = s21_determinant(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);
  ck_assert_double_eq_tol(actual, 5.0, 1e-7);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(determinant_2x2_positive_test) {
  matrix_t dataMatrix;
  int rows = 2;
  int columns = 2;
  double actual;

  s21_create_matrix(rows, columns, &dataMatrix);
  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[1][0] = 3.0;
  dataMatrix.matrix[1][1] = 4.0;

  int codeError = s21_determinant(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);
  ck_assert_double_eq_tol(actual, -2.0, 1e-7);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(determinant_3x3_positive_test) {
  matrix_t dataMatrix;
  int rows = 3;
  int columns = 3;
  double actual;

  s21_create_matrix(rows, columns, &dataMatrix);
  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[0][2] = 3.0;
  dataMatrix.matrix[1][0] = 4.0;
  dataMatrix.matrix[1][1] = 5.0;
  dataMatrix.matrix[1][2] = 6.0;
  dataMatrix.matrix[2][0] = 7.0;
  dataMatrix.matrix[2][1] = 8.0;
  dataMatrix.matrix[2][2] = 9.0;

  int codeError = s21_determinant(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);
  ck_assert_double_eq_tol(actual, 0.0, 1e-7);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(determinant_non_square_test) {
  matrix_t dataMatrix;
  int rows = 2;
  int columns = 3;
  double actual;

  s21_create_matrix(rows, columns, &dataMatrix);

  int codeError = s21_determinant(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(determinant_null_matrix_test) {
  matrix_t *dataMatrix = NULL;
  double actual;

  int codeError = s21_determinant(dataMatrix, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

Suite *suiteDeterminant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("tc_determinant");

  tcase_add_test(tc, determinant_1x1_positive_test);
  tcase_add_test(tc, determinant_2x2_positive_test);
  tcase_add_test(tc, determinant_3x3_positive_test);
  tcase_add_test(tc, determinant_non_square_test);
  tcase_add_test(tc, determinant_null_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}