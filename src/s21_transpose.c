#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (A == NULL || result == NULL || A->rows < 1 || A->columns < 1) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    int rows = A->columns;
    int columns = A->rows;
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return err;
}