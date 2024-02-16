#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QColorDialog>
#include <QDateTime>
#include <QMainWindow>
#include <QUrl>
#include <QtOpenGL/QtOpenGL>
#include <iostream>

#include "lib/3rdparty/giflib/gif_lib.h"
#include "lib/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_action_Exit_triggered();

  void on_pushButton_openFile_2_clicked();

  void on_pushButton_exit_2_clicked();

  void on_pushButton_paint_model_clicked();

  void on_spinBox_Scale_valueChanged(int value);

  void on_Slider_X_move_valueChanged(int value);
  void on_Slider_Y_move_valueChanged(int value);
  void on_Slider_Z_move_valueChanged(int value);

  void on_Slider_X_rotate_valueChanged(int value);
  void on_Slider_Y_rotate_valueChanged(int value);
  void on_Slider_Z_rotate_valueChanged(int value);

  std::string findName(QString filePath);

  void on_pushButton_reset_clicked();

  void on_rb_v_hidden_clicked();
  void on_rb_v_round_clicked();
  void on_rb_v_square_clicked();

  void on_rb_line_solid_clicked();
  void on_rb_line_dotted_clicked();

  void on_Slider_scale_valueChanged(int value);

  void on_pB_colorLine_clicked();

  void on_pB_colorVertex_clicked();
  void on_pB_colorBG_clicked();

  void on_rb_projection_central_clicked();
  void on_rb_projection_parallel_clicked();

  void on_spinBox_vert_size_valueChanged(int arg1);

  void on_spinBox_edge_size_valueChanged(int arg1);

  void save_settings();

  void load_settings();

  void on_pushButton_screenShot_2_clicked();

  void on_action_openFile_triggered();

  void on_action_screenShot_triggered();

  void on_action_info_triggered();

  // void on_action_infoProgram_triggered();

void on_pushButton_gif_2_clicked();

//void make_gif();

  void start_timer_gif();

  void record_gif();

private:
  Ui::MainWindow *ui;
  QString filePath;
  QButtonGroup *vert_type_buttons;
  QButtonGroup *edge_type_buttons;
  QButtonGroup *projection_type_buttons;
  QSettings *settings;
  QString file_name;
  QTimer* timerGIF;  // идентификатор таймера
  int frame;
  QGifImage* gif;
  QFile* ptr_save_file;
//  QString gif_name;
//  QGifImage *gif_frame;
//  int frames_counter = 0;
//  QTimer *timer;
};
#endif  // MAINWINDOW_H
