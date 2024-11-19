#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (!A || !A->matrix || A->rows <= 0 || A->columns <= 0 ||
      A->rows != A->columns) {
    err = INCORRECT_MATRIX_ERROR;
  } else {
    double det = 0.0;
    int det_code = s21_determinant(A, &det);
    if (det_code != OK || fabs(det) < 1e-7) {
      err = CALC_ERROR;
    }

    if (!err) {
      matrix_t complements;
      s21_calc_complements(A, &complements);

      matrix_t transposed;
      s21_transpose(&complements, &transposed);

      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = transposed.matrix[i][j] / det;
        }
      }

      s21_remove_matrix(&complements);
      s21_remove_matrix(&transposed);
    }
  }

  return err;
}