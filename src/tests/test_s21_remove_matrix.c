#include "s21_tests.h"

START_TEST(positive_test) {
  matrix_t actual;
  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &actual);

  ck_assert_ptr_nonnull(actual.matrix);

  s21_remove_matrix(&actual);

  ck_assert_ptr_null(actual.matrix);
  ck_assert_int_eq(actual.rows, 0);
  ck_assert_int_eq(actual.columns, 0);
}
END_TEST

START_TEST(null_pointer_test) { s21_remove_matrix(NULL); }
END_TEST

START_TEST(null_matrix_test) {
  matrix_t actual;
  actual.matrix = NULL;
  actual.rows = 0;
  actual.columns = 0;

  s21_remove_matrix(&actual);
}
END_TEST

Suite *suiteRemoveMatrix(void) {
  Suite *s = suite_create("suite_removeMatrix");
  TCase *tc = tcase_create("tc_removeMatrix");

  tcase_add_test(tc, positive_test);
  tcase_add_test(tc, null_pointer_test);
  tcase_add_test(tc, null_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}