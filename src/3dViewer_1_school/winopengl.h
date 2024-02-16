#ifndef WINOPENGL_H
#define WINOPENGL_H

#include <math.h>

#include <QMessageBox>
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>

#include "mainwindow.h"

extern "C" {
#include "../viewer.h"
}

class WinOpenGL : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit WinOpenGL(QWidget *parent = nullptr);
  virtual ~WinOpenGL();

  double p_red = 1, p_green = 1, p_blue = 1;
  double e_red = 1, e_green = 1, e_blue = 1;
  double bg_red = 0, bg_green = 0, bg_blue = 0;

  data_t object = {0, NULL, 0, NULL};
  QString filename;
  GLfloat normalize_coef;
  void set_normalize_coef();
  void build_points();
  void draw_model_edges();
  // void draw_model_filled();
  void parse_obj();
  void updateProjection();
  //  void mousePressEvent(QMouseEvent *)
  //        override;  // функция вызываемая при нажатии на клавишу мышки
  //    void mouseMoveEvent(
  //        QMouseEvent *) override;  // функция вызываемая при движении мышки
  // MouseMoveControl

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

  double vertices_size = 1;
  double edges_thickness = 1;
  double scale = 50;
  double move_x;
  double move_y;
  double move_z;
  double rotate_x;
  double rotate_y;
  double rotate_z;
  // void wheelEvent(QWheelEvent *event) override;

  // 0 parallel 1 central
  int projection_type = 1;

  // 0 none 1 round 2 square
  int vert_type = 1;
  int vert_size = 1;

  // 0 solid 1 dotted
  int edge_type = 0;
  int edge_size = 1;

 private:
  void initializeGL() override;
  void paintGL() override;
  void resetTransformations();
  QPoint cur_pos;
  QPoint new_pos;
};

#endif  // WINOPENGL_H
