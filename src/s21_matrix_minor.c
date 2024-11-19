#include "s21_matrix.h"

void get_minor(matrix_t *A, matrix_t *minor, int rows, int columns) {
  int mRows = 0, mColumns = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i == rows) continue;

    mColumns = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == columns) continue;

      minor->matrix[mRows][mColumns] = A->matrix[i][j];
      mColumns++;
    }
    mRows++;
  }
}
