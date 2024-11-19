#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int err = OK;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1 ||
      A->rows != A->columns) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
      err = OK;
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      err = OK;
    } else {
      double det = 0.0;
      matrix_t minor;
      for (int j = 0; j < A->columns; j++) {
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        get_minor(A, &minor, 0, j);

        double minor_det = 0.0;
        s21_determinant(&minor, &minor_det);

        det += A->matrix[0][j] * minor_det * ((j % 2 == 0) ? 1 : -1);

        s21_remove_matrix(&minor);
      }

      *result = det;
    }
  }

  return err;
}