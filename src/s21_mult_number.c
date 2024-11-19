#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = OK;
  if (A == NULL || result == NULL) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    if (A->rows <= 0 || A->columns <= 0) {
      err = CALC_ERROR;
    }

    if (!err) {
      if (s21_create_matrix(A->rows, A->columns, result) != OK) {
        err = INCORRECT_MATRIX_ERROR;
      }

      if (!err) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
          }
        }
      }
    }
  }

  return err;
}