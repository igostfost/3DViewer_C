#ifndef VIEWER_H
#define VIEWER_H

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-07

typedef struct data {
  size_t v_count;
  double *vert_arr;
  size_t f_count;
  int *vs_in_fs;
} data_t;

// Parse file
int load_data(char *filename, data_t *data);
int alloc_mem(data_t *data);
void count_vert_and_facet(FILE *file, data_t *data);
void destroy_data(data_t *data);
int parse_vert_and_facet(FILE *file, data_t *data);
// void print_data(data_t *data);

// Transformations
void change_scale(data_t *object, const double k);

void move_X(data_t *object, const double k);
void move_Y(data_t *object, const double k);
void move_Z(data_t *object, const double k);

void rotate_x(data_t *object, double angle);
void rotate_y(data_t *object, double angle);
void rotate_z(data_t *object, double angle);
#endif  // VIEWER_H
