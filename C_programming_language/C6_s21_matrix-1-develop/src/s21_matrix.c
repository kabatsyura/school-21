#include "s21_matrix.h"

/*
0 - OK
1 - Ошибка, некорректная матрица
2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя
провести вычисления и т.д.)
*/

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = IS_NOT_CORRECT;
  if ((rows > 0 && columns > 0) || (rows == 0 && columns > 0) ||
      (rows > 0 && columns == 0))
    error = OK;
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  for (int a = 0; a < rows; ++a) {
    result->matrix[a] = (double *)calloc(columns, sizeof(double));
  }

  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->columns = 0;
  A->rows = 0;
}

/*

#define SUCCESS 1
#define FAILURE 0

Две матрицы A, B совпадают |A = B|, если совпадают их размеры и соответствующие
элементы равны, то есть при всех i, j A(i,j) = B(i,j). Сравнение должно
происходить вплоть до 7 знака после запятой включительно.
*/

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error;
  if ((A->rows == B->rows) && (A->columns == B->columns) && A->matrix != NULL &&
      B->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) < EPS) {
          error = SUCCESS;
        } else {
          error = FAILURE;
          break;
        }
      }
      if (error == FAILURE) {
        break;
      }
    }
  } else {
    error = FAILURE;
  }
  return error;
}

int s21_matrix_check(matrix_t *A) {
  int error = IS_NOT_CORRECT;
  if (((A->rows > 0 && A->columns > 0) || (A->rows == 0 && A->columns > 0) ||
       (A->rows > 0 && A->columns == 0)) &&
      A->matrix != NULL && A != NULL)
    error = OK;
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error =
      (!s21_matrix_check(A) && !s21_matrix_check(B)) ? OK : IS_NOT_CORRECT;
  if (error == OK) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      error = CALC_ERROR;
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error =
      (!s21_matrix_check(A) && !s21_matrix_check(B)) ? OK : IS_NOT_CORRECT;
  if (error == OK) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      error = CALC_ERROR;
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error;
  if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL) {
    error = IS_NOT_CORRECT;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((number == fabs(INFINITY)) || (number == NAN)) {
          error = CALC_ERROR;
          break;
        } else {
          error = OK;
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error =
      (!s21_matrix_check(A) && !s21_matrix_check(B)) ? OK : IS_NOT_CORRECT;
  if (error == OK) {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++)
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }

    } else {
      error = CALC_ERROR;
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error;
  if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL) {
    error = IS_NOT_CORRECT;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
    error = OK;
  }
  return error;
}

void getMatrixForDeterminant(matrix_t *A, int rows, int columns,
                             matrix_t *newA) {
  for (int i = 0, a = 0; i < A->columns; i++) {
    if (i == rows) continue;
    for (int j = 0, b = 0; j < A->columns; j++) {
      if (j == columns) continue;
      newA->matrix[a][b] = A->matrix[i][j];
      b++;
    }
    a++;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error;
  if (A->rows <= 0 || A->columns <= 0 || (A->rows != A->columns) ||
      A->matrix == NULL) {
    error = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double det = 0;
        matrix_t newA;
        s21_create_matrix(A->rows - 1, A->columns - 1, &newA);
        getMatrixForDeterminant(A, i, j, &newA);
        s21_determinant(&newA, &det);
        result->matrix[i][j] = det * pow((-1), (i + j + 2));
        s21_remove_matrix(&newA);
      }
    }
    error = OK;
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error;
  *result = 0;
  int size = A->rows;

  if (A->rows <= 0 || A->columns <= 0 || (A->rows != A->columns) ||
      A->matrix == NULL) {
    error = CALC_ERROR;
  } else {
    if (size == 1) {
      *result = A->matrix[0][0];
    } else if (size == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      double det = 0;
      for (int i = 0; i < A->rows; i++) {
        matrix_t newA;
        s21_create_matrix(size - 1, size - 1, &newA);
        getMatrixForDeterminant(A, 0, i, &newA);
        s21_determinant(&newA, result);
        det += pow(-1, i) * A->matrix[0][i] * (*result);
        s21_remove_matrix(&newA);
      }
      *result = det;
    }
    error = OK;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = s21_matrix_check(A);
  if (error == OK) {
    double det = 0;
    s21_determinant(A, &det);
    if (A->columns == A->rows && (fabs(det) != 0.)) {
      matrix_t minors;
      s21_calc_complements(A, &minors);
      matrix_t matrix_transp;
      s21_transpose(&minors, &matrix_transp);
      s21_mult_number(&matrix_transp, 1. / det, result);
      s21_remove_matrix(&minors);
      s21_remove_matrix(&matrix_transp);
    } else {
      error = CALC_ERROR;
    }
  }
  return error;
}
