#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t dataMatrix, actual, expected;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[1][0] = 3.0;
  dataMatrix.matrix[1][1] = 4.0;

  s21_create_matrix(rows, columns, &expected);
  expected.matrix[0][0] = 1.0;
  expected.matrix[0][1] = 3.0;
  expected.matrix[1][0] = 2.0;
  expected.matrix[1][1] = 4.0;

  int codeError = s21_transpose(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);

  for (int i = 0; i < actual.rows; i++) {
    for (int j = 0; j < actual.columns; j++) {
      ck_assert_double_eq(actual.matrix[i][j], expected.matrix[i][j]);
    }
  }

  s21_remove_matrix(&dataMatrix);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_non_square_matrix_test) {
  matrix_t dataMatrix, actual, expected;
  int rows = 2;
  int columns = 3;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[0][2] = 3.0;
  dataMatrix.matrix[1][0] = 4.0;
  dataMatrix.matrix[1][1] = 5.0;
  dataMatrix.matrix[1][2] = 6.0;

  s21_create_matrix(columns, rows, &expected);
  expected.matrix[0][0] = 1.0;
  expected.matrix[0][1] = 4.0;
  expected.matrix[1][0] = 2.0;
  expected.matrix[1][1] = 5.0;
  expected.matrix[2][0] = 3.0;
  expected.matrix[2][1] = 6.0;

  int codeError = s21_transpose(&dataMatrix, &actual);

  ck_assert_int_eq(codeError, OK);

  for (int i = 0; i < actual.rows; i++) {
    for (int j = 0; j < actual.columns; j++) {
      ck_assert_double_eq(actual.matrix[i][j], expected.matrix[i][j]);
    }
  }

  s21_remove_matrix(&dataMatrix);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_null_pointer_matrix_test) {
  matrix_t *dataMatrix = NULL;
  matrix_t actual;

  int codeError = s21_transpose(dataMatrix, &actual);
  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

START_TEST(transpose_null_pointer_result_test) {
  matrix_t dataMatrix;
  matrix_t *actual = NULL;
  int rows = 2;
  int columns = 3;

  s21_create_matrix(rows, columns, &dataMatrix);
  int codeError = s21_transpose(&dataMatrix, actual);
  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

Suite *suiteTranspose(void) {
  Suite *s = suite_create("suite_transpose");
  TCase *tc = tcase_create("tc_transpose");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, transpose_non_square_matrix_test);
  tcase_add_test(tc, transpose_null_pointer_matrix_test);
  tcase_add_test(tc, transpose_null_pointer_result_test);

  suite_add_tcase(s, tc);
  return s;
}