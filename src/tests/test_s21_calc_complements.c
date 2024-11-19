#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t dataMatrix, actual, expected;
  int rows = 3;
  int columns = 3;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1;
  dataMatrix.matrix[0][1] = 2;
  dataMatrix.matrix[0][2] = 3;
  dataMatrix.matrix[1][0] = 0;
  dataMatrix.matrix[1][1] = 4;
  dataMatrix.matrix[1][2] = 2;
  dataMatrix.matrix[2][0] = 5;
  dataMatrix.matrix[2][1] = 2;
  dataMatrix.matrix[2][2] = 1;

  s21_create_matrix(rows, columns, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  int codeError = s21_calc_complements(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);

  // Сравнение матриц result и expected
  for (int i = 0; i < actual.rows; i++) {
    for (int j = 0; j < actual.columns; j++) {
      ck_assert_double_eq_tol(actual.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&dataMatrix);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_incorrect_test) {
  matrix_t dataMatrix, actual;
  int rows = 2;
  int columns = 3;

  s21_create_matrix(rows, columns, &dataMatrix);

  int codeError = s21_calc_complements(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(calc_complements_null_matrix_test) {
  matrix_t *dataMatrix = NULL;
  matrix_t actual;

  int codeError = s21_calc_complements(dataMatrix, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

Suite *suiteCalcComplements(void) {
  Suite *s = suite_create("suite_calcComplements");
  TCase *tc = tcase_create("tc_calcComplements");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, calc_complements_incorrect_test);
  tcase_add_test(tc, calc_complements_null_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}