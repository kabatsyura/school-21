#include "s21_parsing_object.h"

/**
 * @brief проверка, что лексема - число
 * @param error если 0 - ошибки нет, если 1 - ошибка
 */
int is_digit(char expression) {
  int error = 1;
  if ((expression >= '0' && expression <= '9') || expression == '.') {
    error = 0;
  }
  return error;
}

/**
 * @brief подсчет вершин и полигонов
 * @param error если 0 - ошибки нет, если 1 - ошибка (файла нет)
 * @param path_of_file путь к объекту
 * @param some_data куда записываем данные
 */
int count_vertexes_polygons(char *path_of_file, data_t *some_data) {
  int error = 0;
  int cnt_vertexs = 0;
  int cnt_polygons = 0;
  some_data->count_of_vertex = 0;
  some_data->count_of_polygons = 0;
  some_data->polygons = NULL;
  FILE *file = NULL;
  file = fopen(path_of_file, "r");
  if (file != NULL) {
    char *lineptr = NULL;
    size_t n;
    while (getline(&lineptr, &n, file) != -1) {
      if (lineptr[0] == 'v' && lineptr[1] != 'n' && lineptr[1] != 't') {
        cnt_vertexs++;
      } else if (lineptr[0] == 'f') {
        cnt_polygons++;
      }
    }
    free(lineptr);
  } else {
    error = 1;
  }
  fclose(file);
  some_data->count_of_vertex = cnt_vertexs;
  some_data->count_of_polygons = cnt_polygons;

  return error;
}

/**
 * @brief создание матрицы всех вершин
 * @param error если 0 - ошибки нет, если 1 - ошибка (файла нет)
 * @param path_of_file путь к объекту
 * @param some_data куда записываем данные
 */
int create_matrix_obj(char *path_of_file, data_t *some_data) {
  int error = 0;
  FILE *file;
  file = fopen(path_of_file, "r");
  if (file != NULL) {
    s21_create_matrix(some_data->count_of_vertex, 3, &some_data->matrix);
    char *lineptr = NULL;
    size_t n;
    int rows = 0, columns = 0;
    while (getline(&lineptr, &n, file) != -1) {
      if (lineptr[0] == 'v' && lineptr[1] != 'n' && lineptr[1] != 't') {
        for (int index = 2;
             (lineptr[index] != '\n') || (lineptr[index] != '\0'); index++) {
          if (is_digit(lineptr[index]) == 0 || lineptr[index] == '-') {
            char *start_number = &lineptr[index];
            if (lineptr[index] == '-') index++;
            while (is_digit(lineptr[index]) == 0) {
              index++;
            }
            char *finish_number = &lineptr[--index];
            double number = strtod(start_number, &finish_number);
            some_data->matrix.matrix[rows][columns] = number;

            if (columns < 2) {
              columns++;
            } else {
              columns = 0;
              break;
            }
          } else if (lineptr[index] == ' ') {
            continue;
          }
        }
        rows++;
      }
    }
    free(lineptr);
  } else {
    error = 1;
  }
  fclose(file);
  return error;
}

int note_vertexes_polygons(char *path_of_file, data_t *some_data) {
  int error = 0;
  FILE *file;
  some_data->polygons =
      calloc(some_data->count_of_polygons + 1, sizeof *some_data->polygons);
  file = fopen(path_of_file, "r");
  int count = 0;
  if (file != NULL) {
    char *lineptr = NULL;
    size_t n;
    while (getline(&lineptr, &n, file) != -1) {
      if (lineptr[0] == 'f') {
        for (size_t i = 1; lineptr[i]; i++) {
          if (lineptr[i] >= '0' && lineptr[i] <= '9') {
            if (lineptr[i - 1] == ' ') {
              some_data->polygons[count].numbers_of_vertexes_in_facets++;
            }
          }
        }
        help_funk_vertexes_polygons(lineptr, some_data, count);
        count++;
      }
    }
    free(lineptr);
  } else {
    error = 1;
  }
  fclose(file);
  return error;
}

int help_funk_vertexes_polygons(char *lineptr, data_t *some_data,
                                int count_polygon) {
  int error = 0;
  int tmp_polygon;
  int j = 0;
  some_data->polygons[count_polygon].vertexes = calloc(
      some_data->polygons[count_polygon].numbers_of_vertexes_in_facets * 2,
      sizeof(int));
  for (size_t i = 1; lineptr[i]; i++) {
    if (lineptr[i] >= '0' && lineptr[i] <= '9') {
      if (lineptr[i - 1] == ' ') {
        char tmp[10] = "";
        while (lineptr[i] >= '0' && lineptr[i] <= '9') {
          strncat(tmp, lineptr + i, 1);
          i++;
        }
        tmp_polygon = atoi(tmp);
        some_data->polygons[count_polygon].vertexes[j] = tmp_polygon - 1;
        j++;
        if (j % 2 == 0) {
          some_data->polygons[count_polygon].vertexes[j] = tmp_polygon - 1;
          j++;
        }
        if (j + 1 ==
            some_data->polygons[count_polygon].numbers_of_vertexes_in_facets *
                2) {
          some_data->polygons[count_polygon].vertexes[j] =
              some_data->polygons[count_polygon].vertexes[0];
        }
      }
    }
  }
  return error;
}
void move_obj(data_t *some_data, double x, double y, double z) {
//    printf("%f\n", x);
//    printf("%f\n", y);
//    printf("%f\n", z);
    for (int i = 0; i < some_data->matrix.rows; i++) {
        some_data->matrix.matrix[i][0] += x;
        some_data->matrix.matrix[i][1] += y;
        some_data->matrix.matrix[i][2] += z;
    }
}

void rotation_by_ox(data_t *some_data, double corner) {
    matrix_t tmp;
    tmp  = (*some_data).matrix;
    matrix_t turn_matrix;
    s21_create_matrix(3, 3, &turn_matrix);
    turn_matrix.matrix[0][0] = 1;
    turn_matrix.matrix[0][1] = 0;
    turn_matrix.matrix[0][2] = 0;
    turn_matrix.matrix[1][0] = 0;
    turn_matrix.matrix[1][1] = cos(corner);
    turn_matrix.matrix[1][2] = sin(corner);
    turn_matrix.matrix[2][0] = 0;
    turn_matrix.matrix[2][1] = -sin(corner);
    turn_matrix.matrix[2][2] = cos(corner);
    matrix_t result;
    s21_mult_matrix(&tmp, &turn_matrix, &result);
    (*some_data).matrix = result;
    s21_remove_matrix(&turn_matrix);
    s21_remove_matrix(&tmp);
}

void rotation_by_oy(data_t *some_data, double corner) {
    matrix_t tmp;
    tmp  = (*some_data).matrix;
    matrix_t turn_matrix;
    s21_create_matrix(3, 3, &turn_matrix);
    turn_matrix.matrix[0][0] = cos(corner);
    turn_matrix.matrix[0][1] = 0;
    turn_matrix.matrix[0][2] = -sin(corner);;
    turn_matrix.matrix[1][0] = 0;
    turn_matrix.matrix[1][1] = 1;
    turn_matrix.matrix[1][2] = 0;
    turn_matrix.matrix[2][0] = sin(corner);
    turn_matrix.matrix[2][1] = 0;
    turn_matrix.matrix[2][2] = cos(corner);
    matrix_t result;
    s21_mult_matrix(&tmp, &turn_matrix, &result);
    (*some_data).matrix = result;
    s21_remove_matrix(&turn_matrix);
    s21_remove_matrix(&tmp);
}
void rotation_by_oz(data_t *some_data, double corner) {
    matrix_t tmp;
    tmp  = (*some_data).matrix;
    matrix_t turn_matrix;
    s21_create_matrix(3, 3, &turn_matrix);
    turn_matrix.matrix[0][0] = cos(corner);
    turn_matrix.matrix[0][1] = sin(corner);
    turn_matrix.matrix[0][2] = 0;
    turn_matrix.matrix[1][0] = -sin(corner);
    turn_matrix.matrix[1][1] = cos(corner);
    turn_matrix.matrix[1][2] = 0;
    turn_matrix.matrix[2][0] = 0;
    turn_matrix.matrix[2][1] = 0;
    turn_matrix.matrix[2][2] = 1;
    matrix_t result;
    s21_mult_matrix(&tmp, &turn_matrix, &result);
    (*some_data).matrix = result;
    s21_remove_matrix(&turn_matrix);
    s21_remove_matrix(&tmp);
}

void scale_obj(data_t *some_data, double scale) {
    for (int i = 0; i < some_data->matrix.rows; i++) {
        some_data->matrix.matrix[i][0] *= scale;
        some_data->matrix.matrix[i][1] *= scale;
        some_data->matrix.matrix[i][2] *= scale;
    }
}

void get_max_min_frustum(double *max, double *min, data_t obj) {
    double min_vertex = obj.matrix.matrix[0][0];
    double max_vertex = obj.matrix.matrix[0][1];
    for (int i = 0; i < obj.count_of_vertex; i++) {
        for (int j = 0; j < 3; j++) {
            if (min_vertex > obj.matrix.matrix[i][j]) {
                min_vertex = obj.matrix.matrix[i][j];
            }
            if (max_vertex < obj.matrix.matrix[i][j]) {
                max_vertex = obj.matrix.matrix[i][j];
            }
        }
    }
    *max = max_vertex;
    *min = min_vertex;
}
