#include "viewer.h"

#define L 255

int load_data(char *filename, data_t *data) {
  int error = 0;
  if (filename == NULL || data == NULL) {
    error = 1;
  }
  if (error == 0) {
    FILE *file = fopen(filename, "r");
    if (file) {
      count_vert_and_facet(file, data);
      error = alloc_mem(data);
      if (error != 1) {
        fseek(file, 0, SEEK_SET);
        error = parse_vert_and_facet(file, data);
      }
      fclose(file);
    } else {
      error = 1;
    }
  }
  return error;
}

int alloc_mem(data_t *data) {
  int allocate_status = 0;

  if (data->v_count) {
    data->vert_arr = calloc(data->v_count * 3, sizeof(double));
  }
  if (data->f_count) {
    // *2 потому что для отрисовки линии в glDrawElements нужно 2 вершины
    data->vs_in_fs = calloc(data->f_count * 2, sizeof(int));
  }
  if (data->vert_arr == NULL || data->vs_in_fs == NULL) {
    allocate_status = 1;
  }

  return allocate_status;
}

void count_vert_and_facet(FILE *file, data_t *data) {
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, file) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      data->v_count++;
    } else if (strncmp(line, "f ", 2) == 0) {
      char *f_char_value = strtok(line + 2, " ");
      while (f_char_value != NULL) {
        if (atoi(f_char_value)) {
          data->f_count++;
        }
        f_char_value = strtok(NULL, " ");
      }
    }
  }

  if (line) {
    free(line);
    line = NULL;
  }
}

void destroy_data(data_t *data) {
  if (data != NULL) {
    if (data->vert_arr != NULL) {
      free(data->vert_arr);
      data->vert_arr = NULL;
    }
    if (data->vs_in_fs != NULL) {
      free(data->vs_in_fs);
      data->vs_in_fs = NULL;
    }
  }
}

int parse_vert_and_facet(FILE *file, data_t *data) {
  int error = 0;
  char *line = NULL;
  size_t len = 0;
  size_t i = 0;
  size_t v_cnt = 0;
  size_t f_index_cnt = 0;

  while (getline(&line, &len, file) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      v_cnt++;
      double x, y, z;
      sscanf(line, "v %lf %lf %lf", &x, &y, &z);
      data->vert_arr[i++] = x;
      data->vert_arr[i++] = y;
      data->vert_arr[i++] = z;
    } else if (strncmp(line, "f ", 2) == 0) {
      int first_index = 0;
      int is_first_index = 0;
      char *f_char_value = strtok(line + 2, " ");
      while (f_char_value != NULL) {
        int f_int_value = atoi(f_char_value);
        if (f_int_value) {
          // Если индекс отрицательный, то он относится к концу списка вершин.
          // Например, -1 относится к последнему элементу.
          if (f_int_value < 0) {
            f_int_value += v_cnt + 1;
          }
          data->vs_in_fs[f_index_cnt] = f_int_value - 1;
          if (!is_first_index) {
            first_index = f_int_value - 1;
            is_first_index = 1;
          } else {
            data->vs_in_fs[++f_index_cnt] = f_int_value - 1;
          }
          f_index_cnt++;
        }
        f_char_value = strtok(NULL, " ");
      }
      // loop lines
      data->vs_in_fs[f_index_cnt] = first_index;
      f_index_cnt++;
    }
  }
  if (line) {
    free(line);
    line = NULL;
  }

  if (!data->vert_arr[data->v_count * 3 - 1] ||
      !data->vs_in_fs[data->f_count * 2 - 1]) {
    error = 1;
  }

  return error;
}

// void print_data(data_t *data) {
//   // printing vertices
//   printf("v_count: %ld\n", data->v_count);
//   for (int i = 0; i < (int)data->v_count * 3; i++) {
//     printf("%lf ", data->vert_arr[i]);
//     if ((i + 1) % 3 == 0) {
//       printf("\n");
//     }
//   }
//   printf("\n");
//   // printing vertex_indices
//   printf("f_count: %ld\n", data->f_count);
//   for (int i = 0; i < (int)data->f_count * 2; i++) {
//     printf("%d ", data->vs_in_fs[i]);
//     if ((i + 1) % 6 == 0) {
//       printf("\n");
//     }
//   }
// }