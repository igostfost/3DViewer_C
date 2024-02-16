#include "viewer.h"

void move_X(data_t *object, const double k) {
  for (size_t i = 0; i < object->v_count * 3; i += 3) {
    object->vert_arr[i] += k;
  }
}

void move_Y(data_t *object, const double k) {
  for (size_t i = 1; i < object->v_count * 3; i += 3) {
    object->vert_arr[i] += k;
  }
}

void move_Z(data_t *object, const double k) {
  for (size_t i = 2; i < object->v_count * 3; i += 3) {
    object->vert_arr[i] += k;
  }
}

void change_scale(data_t *object, const double k) {
  if (k != 0) {
    for (size_t i = 0; i < object->v_count * 3; i++) {
      object->vert_arr[i] *= k;
    }
  }
}

void rotate_x(data_t *object, double angle) {
  double old_y, old_z;
  angle *= M_PI / 180;
  for (size_t i = 1; i < object->v_count * 3; i += 3) {
    old_y = object->vert_arr[i];
    old_z = object->vert_arr[i + 1];
    object->vert_arr[i] = old_y * cos(angle) + old_z * sin(angle);
    object->vert_arr[i + 1] = -old_y * sin(angle) + old_z * cos(angle);
  }
}

void rotate_y(data_t *object, double angle) {
  double old_x, old_z;
  angle *= M_PI / 180;
  for (size_t i = 0; i < object->v_count * 3; i += 3) {
    old_x = object->vert_arr[i];
    old_z = object->vert_arr[i + 2];
    object->vert_arr[i] = old_x * cos(angle) + old_z * sin(angle);
    object->vert_arr[i + 2] = -old_x * sin(angle) + old_z * cos(angle);
  }
}

void rotate_z(data_t *object, double angle) {
  double old_x, old_y;
  angle *= M_PI / 180;
  for (size_t i = 0; i < object->v_count * 3; i += 3) {
    old_x = object->vert_arr[i];
    old_y = object->vert_arr[i + 1];
    object->vert_arr[i] = old_x * cos(angle) + old_y * sin(angle);
    object->vert_arr[i + 1] = -old_x * sin(angle) + old_y * cos(angle);
  }
}
