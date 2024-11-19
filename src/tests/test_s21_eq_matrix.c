#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t A, B;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  int codeError = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(codeError, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(not_equal_matrix_test) {
  matrix_t A, B;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.1;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  int codeError = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(codeError, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(case_seventh_decimal_matrix_test) {
  matrix_t A, B;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 1.0000000;
  A.matrix[0][1] = 2.0000000;
  A.matrix[1][0] = 3.0000000;
  A.matrix[1][1] = 4.0000000;

  B.matrix[0][0] = 1.0000001;
  B.matrix[0][1] = 2.0000001;
  B.matrix[1][0] = 3.0000001;
  B.matrix[1][1] = 4.0000001;

  int codeError = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(codeError, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(case_equal_seventh_decimal_matrix_test) {
  matrix_t A, B;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 1.0000000;
  A.matrix[0][1] = 2.0000000;
  A.matrix[1][0] = 3.0000000;
  A.matrix[1][1] = 4.0000000;

  B.matrix[0][0] = 1.0000000;
  B.matrix[0][1] = 2.0000000;
  B.matrix[1][0] = 3.0000000;
  B.matrix[1][1] = 4.0000000;

  int codeError = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(codeError, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(case_not_equal_seventh_decimal_matrix_test) {
  matrix_t A, B;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 1.000000;
  A.matrix[0][1] = 2.000000;
  A.matrix[1][0] = 3.000000;
  A.matrix[1][1] = 4.000000;

  B.matrix[0][0] = 1.0000001;
  B.matrix[0][1] = 2.0000001;
  B.matrix[1][0] = 3.0000001;
  B.matrix[1][1] = 4.0000001;

  int codeError = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(codeError, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(different_size_matrix_test) {
  matrix_t A, B;
  int rowsA = 2;
  int columnsA = 2;
  int rowsB = 3;
  int columnsB = 3;

  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(rowsB, columnsB, &B);

  int codeError = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(codeError, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(first_null_matrix_test) {
  matrix_t *A = NULL;

  matrix_t B;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &B);

  int codeError = s21_eq_matrix(A, &B);

  ck_assert_int_eq(codeError, FAILURE);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(second_null_matrix_test) {
  matrix_t A;
  int rows = 2;
  int columns = 2;
  s21_create_matrix(rows, columns, &A);

  matrix_t *B = NULL;

  int codeError = s21_eq_matrix(&A, B);

  ck_assert_int_eq(codeError, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(two_null_matrix_test) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;

  int codeError = s21_eq_matrix(A, B);

  ck_assert_int_eq(codeError, FAILURE);
}
END_TEST

Suite *suiteEqMatrix(void) {
  Suite *s = suite_create("suite_eqMatrix");
  TCase *tc = tcase_create("tc_eqMatrix");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, not_equal_matrix_test);
  tcase_add_test(tc, case_seventh_decimal_matrix_test);
  tcase_add_test(tc, case_equal_seventh_decimal_matrix_test);
  tcase_add_test(tc, case_not_equal_seventh_decimal_matrix_test);
  tcase_add_test(tc, different_size_matrix_test);
  tcase_add_test(tc, first_null_matrix_test);
  tcase_add_test(tc, second_null_matrix_test);
  tcase_add_test(tc, two_null_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}