#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = OK;
  if (A == NULL || B == NULL || result == NULL || A->columns <= 0 ||
      A->rows <= 0 || B->columns <= 0 || B->rows <= 0) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    if (A->columns != B->rows) {
      err = CALC_ERROR;
    }

    if (!err) {
      int create_result = s21_create_matrix(A->rows, B->columns, result);
      if (create_result != OK) {
        err = INCORRECT_MATRIX_ERROR;
      }

      if (!err) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0.0;
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    }
  }

  return err;
}