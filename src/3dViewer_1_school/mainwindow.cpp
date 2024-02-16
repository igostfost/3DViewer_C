#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QString>

#include "ui_mainwindow.h"
#include "winopengl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->openGLWidget->show();
  QObject::connect(ui->spinBox_Scale, SIGNAL(valueChanged(int)), this,
                   SLOT(on_spinBox_Scale_valueChanged(int)));
  //  QObject::connect(ui->Slider_X_move, SIGNAL(valueChanged(int)), this,
  //                   SLOT(on_Slider_X_move_valueChanged(int)));
  //  QObject::connect(ui->Slider_Y_move, SIGNAL(valueChanged(int)), this,
  //                   SLOT(on_Slider_Y_move_valueChanged(int)));
  //  QObject::connect(ui->Slider_Z_move, SIGNAL(valueChanged(int)), this,
  //                   SLOT(on_Slider_Z_move_valueChanged(int)));
//  vert_type_buttons = new QButtonGroup(this);
//  vert_type_buttons->addButton(ui->rb_v_hidden);
//  vert_type_buttons->addButton(ui->rb_v_round);
//  vert_type_buttons->addButton(ui->rb_v_square);

//  edge_type_buttons = new QButtonGroup(this);
//  edge_type_buttons->addButton(ui->rb_line_solid);
//  edge_type_buttons->addButton(ui->rb_line_dotted);

//  projection_type_buttons = new QButtonGroup(this);
//  projection_type_buttons->addButton(ui->rb_projection_central);
//  projection_type_buttons->addButton(ui->rb_projection_parallel);

  settings = new QSettings("21school", "3D_Viewer", this);
  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  destroy_data(&ui->openGLWidget->object);
  delete settings;
  delete ui;
}

void MainWindow::on_action_Exit_triggered() { close(); }

void MainWindow::on_pushButton_exit_2_clicked() { close(); }

// масштабирование модели
void MainWindow::on_spinBox_Scale_valueChanged(int value) {
  double val = (double)value / ui->openGLWidget->scale;
  change_scale(&ui->openGLWidget->object, val);
  ui->openGLWidget->scale = value;
  //    printf("scale %lf", ui->openGLWidget->scale);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_openFile_2_clicked() {
  filePath = QFileDialog::getOpenFileName(this, tr("Open file"), ".",
                                          tr("Object files (*.obj)"));
  ui->openGLWidget->filename = filePath;
//  destroy_data(&ui->openGLWidget->object);
//  QByteArray inArr = filePath.toUtf8();
//  char *cLine = inArr.data();
//  load_obj_data(cLine, &ui->openGLWidget->object);


  //____________________________________________________________


//  QString QString_filename = QFileDialog::getOpenFileName(
//        this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
//    ui->pathObj->setText(QString_filename);

}
// Определение имени из пути файла
std::string MainWindow::findName(QString filePath) {
  std::string utf8_text = filePath.toUtf8().constData();
  std::string file = utf8_text.substr(utf8_text.rfind('/') + 1);
  //    std::cout << "File name: " << file << std::endl;
  return file;
}

void MainWindow::on_pushButton_paint_model_clicked() {
  ui->openGLWidget->parse_obj();

  QString fin_text = ui->textEdit_fileInfo_2->toPlainText();
  QString fileName = QString::fromStdString(findName(filePath));

  ui->textEdit_fileInfo_2->setTextColor(QColor(255, 255, 255, 255));
  ui->textEdit_fileInfo_2->setPlainText(
      "Имя файла: " + fileName + "\nПуть к файлу: " + filePath +
      "\nКол-во вершин = " + fin_text.setNum(ui->openGLWidget->object.v_count) +
      "\nКол-во поверхностей = " +
      fin_text.setNum(ui->openGLWidget->object.f_count));
}

void MainWindow::on_Slider_X_move_valueChanged(int value) {
  move_X(&ui->openGLWidget->object, (value - ui->openGLWidget->move_x) *
                                        ui->openGLWidget->normalize_coef / 100);
  ui->openGLWidget->move_x = value;
  ui->openGLWidget->update();
}

void MainWindow::on_Slider_Y_move_valueChanged(int value) {
  move_Y(&ui->openGLWidget->object, (value - ui->openGLWidget->move_y) *
                                        ui->openGLWidget->normalize_coef / 100);
  ui->openGLWidget->move_y = value;
  ui->openGLWidget->update();
}

void MainWindow::on_Slider_Z_move_valueChanged(int value) {
  move_Z(&ui->openGLWidget->object, (value - ui->openGLWidget->move_z) *
                                        ui->openGLWidget->normalize_coef / 100);
  ui->openGLWidget->move_z = value;
  ui->openGLWidget->update();
}

void MainWindow::on_Slider_X_rotate_valueChanged(int value) {
  rotate_x(&ui->openGLWidget->object, (value - ui->openGLWidget->rotate_x));
  ui->openGLWidget->rotate_x = value;
  ui->openGLWidget->update();
}

void MainWindow::on_Slider_Y_rotate_valueChanged(int value) {
  rotate_y(&ui->openGLWidget->object, (value - ui->openGLWidget->rotate_y));
  ui->openGLWidget->rotate_y = value;
  ui->openGLWidget->update();
}

void MainWindow::on_Slider_Z_rotate_valueChanged(int value) {
  rotate_z(&ui->openGLWidget->object, (value - ui->openGLWidget->rotate_z));
  ui->openGLWidget->rotate_z = value;
  ui->openGLWidget->update();
}


void MainWindow::on_rb_v_hidden_clicked() {
  ui->openGLWidget->vert_type = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_rb_v_round_clicked() {
  ui->openGLWidget->vert_type = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_rb_v_square_clicked() {
  ui->openGLWidget->vert_type = 2;
  ui->openGLWidget->update();
}

void MainWindow::on_rb_line_solid_clicked() {
  ui->openGLWidget->edge_type = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_rb_line_dotted_clicked() {
  ui->openGLWidget->edge_type = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_Slider_scale_valueChanged(int value) {
  double val = (double)value / ui->openGLWidget->scale;
  change_scale(&ui->openGLWidget->object, val);
  ui->openGLWidget->scale = value;
  //    printf("scale %lf", ui->openGLWidget->scale);
  ui->openGLWidget->update();
  QObject::connect(ui->Slider_scale, SIGNAL(valueChanged(int)),
                   ui->spinBox_Scale, SLOT(setValue(int)));
}

void MainWindow::on_pB_colorLine_clicked() {
  QColor line_color = QColorDialog::getColor(QColor(38, 38, 38, 255));
  if (!line_color.isValid()) {
    qDebug() << "Выбор цвета линии отменён!";
  } else {
    ui->openGLWidget->e_red = line_color.redF();
    ui->openGLWidget->e_green = line_color.greenF();
    ui->openGLWidget->e_blue = line_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "edge: rgb(%d,%d,%d)", line_color.red(),
            line_color.green(), line_color.blue());
    ui->openGLWidget->update();
  }
}

void MainWindow::on_pB_colorVertex_clicked() {
  QColor points_color = QColorDialog::getColor(QColor(38, 38, 38, 255));
  if (!points_color.isValid()) {
    qDebug() << "Выбор цвета Точки отменён!";
  } else {
    ui->openGLWidget->p_red = points_color.redF();
    ui->openGLWidget->p_green = points_color.greenF();
    ui->openGLWidget->p_blue = points_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "points: rgb(%d,%d,%d)", points_color.red(),
            points_color.green(), points_color.blue());
    ui->openGLWidget->update();
  }
}

void MainWindow::on_pB_colorBG_clicked() {
  QColor bg_color =
      QColorDialog::getColor(QColor(38, 38, 38, 255));  // 0.15, 0.15, 0.15
  if (!bg_color.isValid()) {
    qDebug() << "Выбор цвета фона отменён!";
  } else {
    ui->openGLWidget->bg_red = bg_color.redF();
    ui->openGLWidget->bg_green = bg_color.greenF();
    ui->openGLWidget->bg_blue = bg_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", bg_color.red(),
            bg_color.green(), bg_color.blue());
    ui->openGLWidget->update();
  }
}

void MainWindow::on_rb_projection_central_clicked() {
  ui->openGLWidget->projection_type = 1;
  //on_pushButton_reset_clicked();
  ui->openGLWidget->updateProjection();
}

void MainWindow::on_rb_projection_parallel_clicked() {
  ui->openGLWidget->projection_type = 0;
  //on_pushButton_reset_clicked();
  ui->openGLWidget->updateProjection();
}

void MainWindow::on_spinBox_vert_size_valueChanged(int value) {
  ui->openGLWidget->vert_size = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spinBox_edge_size_valueChanged(int value) {
  ui->openGLWidget->edge_size = value;
  ui->openGLWidget->update();
}

void MainWindow::save_settings() {
  settings->setValue("are_settings", 1);
  settings->setValue("projection_type", ui->openGLWidget->projection_type);
  settings->setValue("vert_type", ui->openGLWidget->vert_type);
  settings->setValue("vert_size", ui->openGLWidget->vert_size);
  settings->setValue("v_red", ui->openGLWidget->p_red);
  settings->setValue("v_green", ui->openGLWidget->p_green);
  settings->setValue("v_blue", ui->openGLWidget->p_blue);
  settings->setValue("edges_type", ui->openGLWidget->edge_type);
  settings->setValue("edges_size", ui->openGLWidget->edge_size);
  settings->setValue("e_red", ui->openGLWidget->e_red);
  settings->setValue("e_green", ui->openGLWidget->e_green);
  settings->setValue("e_blue", ui->openGLWidget->e_blue);
  settings->setValue("bg_red", ui->openGLWidget->bg_red);
  settings->setValue("bg_green", ui->openGLWidget->bg_green);
  settings->setValue("bg_blue", ui->openGLWidget->bg_blue);
}

void MainWindow::on_pushButton_reset_clicked() {
  ui->openGLWidget->scale = 50;
  ui->spinBox_Scale->setValue(50);

  ui->Slider_X_move->setValue(0);
  //    ui->openGLWidget->move_y = 0;
  ui->Slider_Y_move->setValue(0);
  //  ui->openGLWidget->move_z = 0;
  ui->Slider_Z_move->setValue(0);
  //  ui->openGLWidget->rotate_x = 0;
  ui->Slider_X_rotate->setValue(0);
  //  ui->openGLWidget->rotate_y = 0;
  ui->Slider_Y_rotate->setValue(0);
  //  ui->openGLWidget->rotate_z = 0;
  ui->Slider_Z_rotate->setValue(0);

  ui->openGLWidget->vert_type = 1;
  ui->rb_v_round->setChecked(1);

  ui->openGLWidget->edge_type = 0;
  ui->rb_line_solid->setChecked(1);

  ui->openGLWidget->projection_type = 1;
  ui->rb_projection_central->setChecked(1);

   ui->openGLWidget->vert_size = 1;
   ui->spinBox_vert_size->setValue(1);

   ui->openGLWidget->edge_size = 1;
   ui->spinBox_edge_size->setValue(1);

  ui ->openGLWidget->p_red = 1;
  ui ->openGLWidget->p_green = 1;
  ui ->openGLWidget->p_blue = 1;
  ui ->openGLWidget->e_red = 1;
  ui ->openGLWidget->e_green = 1;
  ui ->openGLWidget->e_blue = 1;
  ui ->openGLWidget->bg_red = 0;
  ui ->openGLWidget->bg_green = 0;
  ui ->openGLWidget->bg_blue = 0;

  ui->openGLWidget->update();

  //  ui->openGLWidget->updateProjection();
}

void MainWindow::load_settings() {
  if (settings->value("are_settings").toInt()) {
    char rgba_color[40];
//    ui->openGLWidget->projection_type = settings->value("projection_type").toInt();
   int projection_mode = settings->value("projection_type").toInt();
    if(projection_mode == 0){
         ui->rb_projection_parallel->setChecked(true);
            ui->openGLWidget->projection_type = 0;
    } else if(projection_mode == 1){
        ui->rb_projection_central->setChecked(true);
        ui->openGLWidget->projection_type = 1;
    }
//    ui->comboBox_projection->setCurrentIndex(
//        settings->value("projection_type").toInt());
    int v_mode = settings->value("v_display_method").toInt();
    if (v_mode == 0) {
      ui->rb_v_hidden->setChecked(true);
      ui->openGLWidget->vert_type = 0;
    } else if (v_mode == 1) {
      ui->rb_v_round->setChecked(true);
      ui->openGLWidget->vert_type = 1;
    } else if (v_mode == 2) {
      ui->rb_v_square->setChecked(true);
      ui->openGLWidget->vert_type = 2;
    }
    ui->spinBox_vert_size->setValue(settings->value("vert_size").toDouble());
    ui->openGLWidget->p_red = settings->value("v_red").toDouble();
    ui->openGLWidget->p_green = settings->value("v_green").toDouble();
    ui->openGLWidget->p_blue = settings->value("v_blue").toDouble();
    sprintf(rgba_color, "vertex-color: rgb(%d,%d,%d)",
            (int)(ui->openGLWidget->p_red * 255),
            (int)(ui->openGLWidget->p_green * 255),
            (int)(ui->openGLWidget->p_blue * 255));
    int edges_mode = settings->value("edges_type").toInt();
    if (edges_mode == 0) {
      ui->rb_line_solid->setChecked(true);
      ui->openGLWidget->edge_type = 0;
    } else if (edges_mode == 1) {
      ui->rb_line_dotted->setChecked(true);
      ui->openGLWidget->edge_type = 1;
    }
    int vert_mode = settings->value("vert_type").toInt();
    if (vert_mode == 0) {
      ui->rb_v_hidden->setChecked(true);
      ui->openGLWidget->vert_type = 0;
    } else if (vert_mode == 1) {
      ui->rb_v_round->setChecked(true);
      ui->openGLWidget->vert_type = 1;
    }else if (vert_mode == 2) {
        ui->rb_v_square->setChecked(true);
        ui->openGLWidget->vert_type = 2;
      }
    ui->spinBox_edge_size->setValue(settings->value("edges_size").toInt());
    ui->openGLWidget->e_red = settings->value("e_red").toDouble();
    ui->openGLWidget->e_green = settings->value("e_green").toDouble();
    ui->openGLWidget->e_blue = settings->value("e_blue").toDouble();
    sprintf(rgba_color, "edges-color: rgb(%d,%d,%d)",
            (int)(ui->openGLWidget->e_red * 255),
            (int)(ui->openGLWidget->e_green * 255),
            (int)(ui->openGLWidget->e_blue * 255));
    ui->openGLWidget->bg_red = settings->value("bg_red").toDouble();
    ui->openGLWidget->bg_green = settings->value("bg_green").toDouble();
    ui->openGLWidget->bg_blue = settings->value("bg_blue").toDouble();
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)",
            (int)(ui->openGLWidget->bg_red * 255),
            (int)(ui->openGLWidget->bg_green * 255),
            (int)(ui->openGLWidget->bg_blue * 255));
  }
}


void MainWindow::on_pushButton_screenShot_2_clicked()
{

QFileDialog dialogConnectImage(this);
QDateTime date = QDateTime::currentDateTime();
QString format_date = date.toString("yyyy-MM-dd hh.mm.ss");
QString name_screen_shot = "Screen Shot " + format_date + ".jpeg";
QString name_img = dialogConnectImage.getSaveFileName(
this, tr("Save a screenshot"), name_screen_shot,tr("image (*.jpeg *.bmp)"));
     if (name_img.length() >= 1) {
          QImage img = ui->openGLWidget->grabFramebuffer();
          img.save(name_img);
          QMessageBox messageBoxImage;
          messageBoxImage.information(0, "", "Screenshot saved successfully");
        }
}


void MainWindow::on_pushButton_gif_2_clicked()
{
    QString filter = "*.gif";
        file_name = "/0";
        file_name = QFileDialog::getSaveFileName(this, "Сохранить GIF", QDir::homePath(), filter);

        ptr_save_file = new QFile(file_name);
        if (!ptr_save_file->open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Warning", "Не удалось записать файл");
        } else {
            start_timer_gif();
        }
}


void MainWindow::start_timer_gif() {
//    const QRect rect(0, 0, ui->openGLWidget->width(), ui->openGLWidget->height());
    gif = new QGifImage(QSize(640, 480));
    timerGIF = new QTimer(this);
    connect(timerGIF, &QTimer::timeout, this, &MainWindow::record_gif);
    timerGIF->start(100);
    frame = 0;
}



void MainWindow::record_gif() {
    qDebug() << ui->openGLWidget->width();
    qDebug() << ui->openGLWidget->height();
    const QRect rect(0, 0, 640, 480);
    QPixmap pixmap = ui->openGLWidget->grab(rect);

    qDebug() << "pixmap = " << pixmap;

    QImage myImage = pixmap.toImage();
    frame++;
    gif->addFrame(myImage, 100);  // цифра это задержка
    if (frame == 50) {
        timerGIF->stop();
        gif->save(ptr_save_file);
        ptr_save_file->close();
        delete ptr_save_file;
        ptr_save_file = nullptr;
        delete gif;
        gif = nullptr;
        QMessageBox::about(this, "Статус", "GIF сохранена");
    }
}



//void MainWindow::on_pushButton_gif_2_clicked(){

//    QDateTime current_date = QDateTime::currentDateTime();
//        QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
//        QString name_pattern = "Screen Cast " + formattedTime + ".gif";
//        gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
//                                                name_pattern, tr("gif (*.gif)"));
//        if (gif_name != "") {
//          gif_frame = new QGifImage;
//          gif_frame->setDefaultDelay(10);
//          timer->setInterval(100);
//          timer->start();
//        }

//}

//void MainWindow::make_gif() {
//  QImage image = ui->openGLWidget->grabFramebuffer();
//  QSize image_size(640, 480);
//  QImage scaled_image = image.scaled(image_size);
//  gif_frame->addFrame(scaled_image);
//  if (frames_counter == 50) {
//    timer->stop();
//    gif_frame->save(gif_name);
//    frames_counter = 0;
//    QMessageBox messageBoxGif;
//    messageBoxGif.information(0, "", "Gif animation saved successfully");
//    delete gif_frame;
//  }
//  frames_counter++;
//}



void MainWindow::on_action_openFile_triggered()
{
    on_pushButton_openFile_2_clicked();
}


void MainWindow::on_action_screenShot_triggered()
{
    on_pushButton_screenShot_2_clicked();
}


void MainWindow::on_action_info_triggered()
{
    QMessageBox msg;
       msg.setWindowTitle("О программе 3DViewer");
       msg.setIcon(QMessageBox::Information);
       msg.setText("  Программа 3DViewer_v1.0 предназначена для просмотра 3D-моделей.\n\n"
                   "  Авторы:\n"
                   "    Леша - oceanusp;\n"
                   "    Аня  - greatem;\n"
                   "  Программа реализована в рамках учебной программы в School21.\n"
                   "  Возможности программы:\n"
                   "- распознавание и отображение файлов с разрешением *.obj;\n"
                   "- двигает, вращает и масштабирует 3D-модель;\n"
                   "- настраивает отображение модели (цвет и толщину линий, цвет и размер вершин, цвет фона);\n"
                   "- создание GIF-анимации.");
       msg.exec();
}


//void MainWindow::on_action_infoProgram_triggered()
//{
//    QString path = "index.html";
//      QDesktopServices::openUrl(QUrl("file://" + path));
//}

