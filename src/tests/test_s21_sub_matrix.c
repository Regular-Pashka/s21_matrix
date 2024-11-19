#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t A, B, actual;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 6.0;
  A.matrix[1][0] = 7.0;
  A.matrix[1][1] = 8.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  matrix_t expected;
  s21_create_matrix(rows, columns, &expected);
  expected.matrix[0][0] = 4.0;
  expected.matrix[0][1] = 4.0;
  expected.matrix[1][0] = 4.0;
  expected.matrix[1][1] = 4.0;

  int codeError = s21_sub_matrix(&A, &B, &actual);

  ck_assert_int_eq(codeError, OK);

  for (int i = 0; i < actual.rows; i++) {
    for (int j = 0; j < actual.columns; j++) {
      ck_assert_double_eq(actual.matrix[i][j], expected.matrix[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&actual);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(different_sizes_matrix_test) {
  matrix_t A, B, actual;
  int rowsA = 2;
  int columnsA = 2;
  int rowsB = 3;
  int columnsB = 3;
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(rowsB, columnsB, &B);

  int codeError = s21_sub_matrix(&A, &B, &actual);

  ck_assert_int_eq(codeError, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_pointers_first_matrix_test) {
  matrix_t *A = NULL;
  matrix_t B, actual;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &B);

  int codeError = s21_sub_matrix(A, &B, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_pointers_second_matrix_test) {
  matrix_t A, actual;
  matrix_t *B = NULL;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);

  int codeError = s21_sub_matrix(&A, B, &actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_pointers_result_matrix_test) {
  matrix_t A, B;
  matrix_t *actual = NULL;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  int codeError = s21_sub_matrix(&A, &B, actual);

  ck_assert_int_eq(codeError, INCORRECT_MATRIX_ERROR);
  ck_assert_ptr_null(actual);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suiteSubMatrix(void) {
  Suite *s = suite_create("suite_subMatrix");
  TCase *tc = tcase_create("tc_subMatrix");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, different_sizes_matrix_test);
  tcase_add_test(tc, null_pointers_first_matrix_test);
  tcase_add_test(tc, null_pointers_second_matrix_test);
  tcase_add_test(tc, null_pointers_result_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}