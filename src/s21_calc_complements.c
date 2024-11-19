#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1 ||
      A->rows != A->columns) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    if (A->rows == 1) {
      result->matrix[0][0] = 1;
      err = OK;
    } else {
      matrix_t minor;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          get_minor(A, &minor, i, j);

          double determinant = 0.0;
          s21_determinant(&minor, &determinant);

          result->matrix[i][j] = determinant * ((i + j) % 2 == 0 ? 1.0 : -1.0);

          s21_remove_matrix(&minor);
        }
      }
    }
  }

  return err;
}