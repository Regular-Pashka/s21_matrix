#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t actual;
  int rows = 3;
  int columns = 3;
  double expected[3][3] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

  int codeError = s21_create_matrix(rows, columns, &actual);

  ck_assert_int_eq(codeError, OK);
  ck_assert_ptr_nonnull(actual.matrix);
  ck_assert_int_eq(actual.rows, rows);
  ck_assert_int_eq(actual.columns, columns);

  for (int i = 0; i < actual.rows; i++) {
    for (int j = 0; j < actual.columns; j++) {
      ck_assert_double_eq(actual.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&actual);

  ck_assert_ptr_null(actual.matrix);
  ck_assert_int_eq(actual.rows, 0);
  ck_assert_int_eq(actual.columns, 0);
}
END_TEST

START_TEST(one_rows_and_columns_test) {
  matrix_t actual;
  int rows = 1;
  int columns = 1;
  double expected[1][1] = {{0.0}};

  int codeError = s21_create_matrix(rows, columns, &actual);

  ck_assert_int_eq(codeError, OK);
  ck_assert_ptr_nonnull(actual.matrix);
  ck_assert_int_eq(actual.rows, rows);
  ck_assert_int_eq(actual.columns, columns);

  for (int i = 0; i < actual.rows; i++) {
    for (int j = 0; j < actual.columns; j++) {
      ck_assert_double_eq(actual.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&actual);

  ck_assert_ptr_null(actual.matrix);
  ck_assert_int_eq(actual.rows, 0);
  ck_assert_int_eq(actual.columns, 0);
}
END_TEST

START_TEST(zero_rows_test) {
  matrix_t actual;
  int rows = 0;
  int columns = 5;

  int codeError = s21_create_matrix(rows, columns, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

START_TEST(zero_columns_test) {
  matrix_t actual;
  int rows = 5;
  int columns = 0;

  int codeError = s21_create_matrix(rows, columns, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

START_TEST(negative_rows_test) {
  matrix_t actual;
  int rows = -2;
  int columns = 2;

  int codeError = s21_create_matrix(rows, columns, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

START_TEST(negative_columns_test) {
  matrix_t actual;
  int rows = 5;
  int columns = -5;

  int codeError = s21_create_matrix(rows, columns, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

START_TEST(null_pointer_test) {
  matrix_t *actual = NULL;
  int rows = 5;
  int columns = 5;

  int codeError = s21_create_matrix(rows, columns, actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
}
END_TEST

Suite *suiteCreateMatrix(void) {
  Suite *s = suite_create("suite_createMatrix");
  TCase *tc = tcase_create("tc_createMatrix");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, one_rows_and_columns_test);
  tcase_add_test(tc, zero_rows_test);
  tcase_add_test(tc, zero_columns_test);
  tcase_add_test(tc, negative_rows_test);
  tcase_add_test(tc, negative_columns_test);
  tcase_add_test(tc, null_pointer_test);

  suite_add_tcase(s, tc);
  return s;
}