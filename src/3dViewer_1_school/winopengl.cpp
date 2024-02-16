#define GL_SILENCE_DEPRECATION
#include "winopengl.h"

#include <QDebug>
#include <iostream>

#include "mainwindow.h"

#ifdef Q_OS_MAC
#include <glu.h>
#elif linux
#include <GL/glu.h>
// #else
//     #error "We don't support that version yet..."
#endif

WinOpenGL::~WinOpenGL() {
  // destroy_data(&object);
}

WinOpenGL::WinOpenGL(QWidget* parent) : QOpenGLWidget(parent) { parse_obj(); }

void WinOpenGL::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void WinOpenGL::paintGL() {
  glClearColor(this->bg_red, this->bg_green, this->bg_blue, 1.0);

  // Clear the color and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glVertexPointer(3, GL_DOUBLE, 0,
                    object.vert_arr);

  // Set the current matrix mode to projection matrix
  glMatrixMode(GL_PROJECTION);

  // Load the identity matrix to reset any previous transformations
  glLoadIdentity();


  // Set the color to white
  //glColor3f(1.0f, 1.0f, 1.0f);

  // Apply the chosen projection transformation
  if (this->projection_type == 1) {  // центральная
                                     //        printf("im here");
    glFrustum(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
              1 * normalize_coef, normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, 0, -2 * normalize_coef);
    glRotatef(30, 1, 0, 0);
  } else if (this->projection_type == 0) {  // параллельная
    glOrtho(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
            1 * normalize_coef, -1 * normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, -normalize_coef / 2, 0);
  }

  // Enable the vertex array client state to draw vertices
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, object.vert_arr);

  // Call the function to draw the points of the model
  if (vert_type) {
    build_points();
  }

  // Call the function to draw the edges of the model
  draw_model_edges();
  //    draw_model_filled();

  // Disable the vertex array client state as it's no longer needed
  glDisableClientState(GL_VERTEX_ARRAY);
}

void WinOpenGL::parse_obj() {

    destroy_data(&object);
    QByteArray inArr = filename.toUtf8();
    char *cLine = inArr.data();
    load_data(cLine, &object);

  set_normalize_coef();
  update();
}

void WinOpenGL::set_normalize_coef() {
  // Initialize the normalize_coef to a negative value to ensure it will be
  // updated correctly
  normalize_coef = -10;

  // Loop through each vertex in the object's vertex array to find the maximum
  // absolute coordinate value
  for (size_t i = 0; i < object.v_count * 3; i++) {
    // Check if the absolute value of the current vertex coordinate is greater
    // than the current normalize_coef If so, update the normalize_coef with the
    // new maximum absolute value
    if (abs(object.vert_arr[i]) > normalize_coef) {
      normalize_coef = abs(object.vert_arr[i]);
    }
  }
}

void WinOpenGL::build_points() {
  if (vert_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  vertices_size = (double)vert_size;
  glPointSize(this->vertices_size);
  glColor3f(p_red, p_green, p_blue);
  glDrawArrays(GL_POINTS, 0, object.v_count);
  if (vert_type == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void WinOpenGL::resetTransformations() {
  rotate_x = 0.0f;
  rotate_y = 0.0f;
  rotate_z = 0.0f;
  move_x = 0.0f;
  move_y = 0.0f;
  move_z = 0.0f;
  scale = 50.0f;
}

void WinOpenGL::updateProjection() {
  set_normalize_coef();
  update();
}

void WinOpenGL::draw_model_edges() {
  if (this->edge_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  edges_thickness = (double)edge_size;
  glLineWidth(this->edges_thickness);
  // Set the polygon mode to draw lines instead of filled polygons
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  resetTransformations();
  // Set the color for the edges to white
  glColor3f(e_red, e_green, e_blue);
  glDrawElements(GL_LINES, object.f_count * 2, GL_UNSIGNED_INT,
                   object.vs_in_fs);  // multiply by two because we draw
                                              // lines that close

//  // Loop through each polygon (face) of the 3D model
//  for (size_t i = 0; i < object.f_count; i++) {
//    // Start drawing the line loop for the current polygon
//    glBegin(GL_LINE_LOOP);
//    // Loop through each vertex of the current polygon
//    for (int j = 0; j < object.polygons[i].num_of_vs_in_fs; j++) {
//      // Get the index of the current vertex
//      int vertexIndex = object.polygons[i].vertexes[j];
//      // Get the coordinates of the vertex and draw it as part of the line
//      // loop
//      glVertex3f(object.vert_arr[vertexIndex * 3],      // X-coordinate
//                 object.vert_arr[vertexIndex * 3 + 1],  // Y-coordinate
//                 object.vert_arr[vertexIndex * 3 + 2]   // Z-coordinate
//      );
//    }
//    // End the line loop for the current polygon
//    glEnd();
//  }

//  // Restore the polygon mode to draw filled polygons (default mode)
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (this->edge_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}


//// ---------- start Настройка мыши ----------

//void WinOpenGL::mousePressEvent(QMouseEvent* mousePress)
//{
//    mPos = mousePress->pos();
//}

//void WinOpenGL::mouseMoveEvent(QMouseEvent* mouseEvent)
//{
//    float kx = 0.01;  // коэффициент для замедления вращения модели
//    float ky = 0.01;  // коэффициент для замедления вращения модели
//    rotate_x += kx * 180 / (M_PI) * (mouseEvent->pos().y() - mPos.y());
//    rotate_y += ky * 180 / (M_PI) * (mouseEvent->pos().x() - mPos.x());
//    mPos = mouseEvent->pos();
//}

//// ---------- finish Настройка мыши ----------
///

void WinOpenGL::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);

  if (event->buttons() & Qt::LeftButton) {
    move_x += new_pos.x() * normalize_coef / 5000;
    move_y += -new_pos.y() * normalize_coef / 5000;
    update();
  } else if (event->buttons() & Qt::RightButton) {
    rotate_x += -new_pos.y() * 0.005;
    rotate_y += new_pos.x() * 0.005;
    update();
  }
}

void WinOpenGL::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 120;
  double step = normalize_coef / 10;
  double scale_tmp = scale;
  if ((int)(scale + numDegrees.y() * step) > 0) {
    scale += numDegrees.y() * step;
    scale += scale / scale_tmp;
    update();
  }
}

void WinOpenGL::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}

