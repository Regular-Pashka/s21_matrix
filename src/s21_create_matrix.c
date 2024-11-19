#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = OK;
  if (rows < 1 || columns < 1 || result == NULL) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return err;
}