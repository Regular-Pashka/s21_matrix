#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t dataMatrix, actual;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[1][0] = 3.0;
  dataMatrix.matrix[1][1] = 4.0;

  double dataNumber = 5;

  matrix_t expected;
  s21_create_matrix(rows, columns, &expected);
  expected.matrix[0][0] = 5.0;
  expected.matrix[0][1] = 10.0;
  expected.matrix[1][0] = 15.0;
  expected.matrix[1][1] = 20.0;

  int codeError = s21_mult_number(&dataMatrix, dataNumber, &actual);

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

START_TEST(negative_sizes_rows_data_matrix_test) {
  matrix_t dataMatrix, actual;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[1][0] = 3.0;
  dataMatrix.matrix[1][1] = 4.0;
  dataMatrix.rows = -1;

  double dataNumber = 5;

  int codeError = s21_mult_number(&dataMatrix, dataNumber, &actual);

  ck_assert_int_eq(codeError, CALC_ERROR);

  dataMatrix.rows = 2;
  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(negative_sizes_columns_data_matrix_test) {
  matrix_t dataMatrix, actual;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[1][0] = 3.0;
  dataMatrix.matrix[1][1] = 4.0;
  dataMatrix.columns = -1;

  double dataNumber = 5;

  int codeError = s21_mult_number(&dataMatrix, dataNumber, &actual);

  ck_assert_int_eq(codeError, CALC_ERROR);

  dataMatrix.columns = 2;
  s21_remove_matrix(&dataMatrix);
}
END_TEST

START_TEST(null_pointers_data_matrix_test) {
  matrix_t *dataMatrix = NULL;
  matrix_t actual;

  double dataNumber = 5;

  int codeError = s21_mult_number(dataMatrix, dataNumber, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

START_TEST(null_pointers_result_matrix_test) {
  matrix_t dataMatrix;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &dataMatrix);

  dataMatrix.matrix[0][0] = 1.0;
  dataMatrix.matrix[0][1] = 2.0;
  dataMatrix.matrix[1][0] = 3.0;
  dataMatrix.matrix[1][1] = 4.0;

  matrix_t *actual = NULL;

  double dataNumber = 5;

  int codeError = s21_mult_number(&dataMatrix, dataNumber, actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
  ck_assert_ptr_null(actual);

  s21_remove_matrix(&dataMatrix);
}
END_TEST

Suite *suiteMultNumber(void) {
  Suite *s = suite_create("suite_multNumber");
  TCase *tc = tcase_create("tc_multNumber");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, negative_sizes_rows_data_matrix_test);
  tcase_add_test(tc, negative_sizes_columns_data_matrix_test);
  tcase_add_test(tc, null_pointers_data_matrix_test);
  tcase_add_test(tc, null_pointers_result_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}