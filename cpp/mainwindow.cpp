#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "../viewer.h"
#ifdef __cplusplus
}
#endif


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("s21 3DViewer");
 //   ui->widget->load_settings();  // авто загрузка с последними настройками

    ui->x_value_rot->setValidator(new QDoubleValidator(this));
    ui->y_value_rot->setValidator(new QDoubleValidator(this));
    ui->z_value_rot->setValidator(new QDoubleValidator(this));
    ui->x_value_tr->setValidator(new QDoubleValidator(this));
    ui->y_value_tr->setValidator(new QDoubleValidator(this));
    ui->z_value_tr->setValidator(new QDoubleValidator(this));
    ui->scale_value->setValidator(new QDoubleValidator(this));

    // bonus part
    ui->central->setChecked(true);  // projection
    ui->radio_jpg->setChecked(true); // save screen
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_button_clicked()
{
    QString file_str = QFileDialog::getOpenFileName(0, "Bazinga!", "", "*.obj");
    QByteArray ba_amount = file_str.toLocal8Bit();
    char *filename = ba_amount.data();
    int counter = 0;
    for (size_t i = 0; i < strlen(filename); i++) {
        if (filename[i] == '/') {
            counter++;
        }
    }
    char window_name[1000] = {'\0'};
    int check = 0;
    int j = 0;
    for (size_t i = 0; i < strlen(filename); i++) {
        if (check == counter) {
            window_name[j] = filename[i];
            j++;
        }
        if (filename[i] == '/') {
            check++;
        }
    }
    setWindowTitle(window_name);
    ui->widget->initObject(filename);

    // add info into InfoBox
    ui->filename_value->setText(window_name);
    ui->full_filename_label->setText(filename); // путь к файлу, не обязательно

    struct data newfile;
    first_file_reading(filename, &newfile);
    unsigned int vertex_counter = newfile.number_of_vertexes;
    QString vertext_string = QString::number(vertex_counter);
    ui->vertices_value->setText(vertext_string); // кол-во вершин

    int edges_counter = newfile.count_for_polygons;  // count_for_polygons
    QString edges_string = QString::number(edges_counter / 2);
    ui->edges_value->setText(edges_string); // кол-во (пока стороны?)

}


void MainWindow::on_transition_reset_clicked()
{
    ui->widget->Transition_reset();
//    ui->x_value_tr->setText("0");
//    ui->y_value_tr->setText("0");
//    ui->z_value_tr->setText("0");
}


void MainWindow::on_scale_apply_clicked()
{
    if (ui->scale_value->text() == "") ui->scale_value->setText("0");
    QString Scale_k = ui->scale_value->text();
    Scale_k.replace(",", ".");
    double k = Scale_k.toDouble();
    ui->widget->Scale_apply(k);
    ui->scale_value->setText("0");
}


void MainWindow::on_scale_reset_clicked()
{
    ui->widget->Scale_reset();
    ui->scale_value->setText("0");
}


void MainWindow::on_x_rotate_clicked()
{
    if (ui->x_value_rot->text() == "") ui->x_value_rot->setText("0");
    QString x_value_str = ui->x_value_rot->text();
    x_value_str.replace(",", ".");
    double x_value = x_value_str.toDouble();
    ui->widget->set_x_rotate(x_value);
}


void MainWindow::on_y_rotate_clicked()
{
    if (ui->y_value_rot->text() == "") ui->y_value_rot->setText("0");
    QString y_value_str = ui->y_value_rot->text();
    y_value_str.replace(",", ".");
    double y_value = y_value_str.toDouble();
    ui->widget->set_y_rotate(y_value);
}


void MainWindow::on_z_rotate_clicked()
{
    if (ui->z_value_rot->text() == "") ui->z_value_rot->setText("0");
    QString z_value_str = ui->z_value_rot->text();
    z_value_str.replace(",", ".");
    double z_value = z_value_str.toDouble();
    ui->widget->set_z_rotate(z_value);
}

void MainWindow::on_x_move_clicked()
{
    if (ui->x_value_tr->text() == "") ui->x_value_tr->setText("0");
    QString x_value_str = ui->x_value_tr->text();
    x_value_str.replace(",", ".");
    double x_value = x_value_str.toDouble();
    ui->widget->set_x_move(x_value);
}


void MainWindow::on_y_move_clicked()
{
    if (ui->y_value_tr->text() == "") ui->y_value_tr->setText("0");
    QString y_value_str = ui->y_value_tr->text();
    y_value_str.replace(",", ".");
    double y_value = y_value_str.toDouble();
    ui->widget->set_y_move(y_value);
}


void MainWindow::on_z_move_clicked()
{
    if (ui->z_value_tr->text() == "") ui->z_value_tr->setText("0");
    QString z_value_str = ui->z_value_tr->text();
    z_value_str.replace(",", ".");
    double z_value = z_value_str.toDouble();
    ui->widget->set_z_move(z_value);
}

// rotate sliders

void MainWindow::on_x_slider_valueChanged(int value)
{
    double x_value = ui->x_slider->value();
    ui->widget->set_x_rotate(x_value);  // заменить на move ?
}

void MainWindow::on_y_slider_valueChanged(int value)
{
//    ui->label->setText(QString::number(ui->y_slider->value()));
    double y_value = ui->y_slider->value();
    ui->widget->set_y_rotate(y_value);  // заменить на move ?
}

void MainWindow::on_z_slider_valueChanged(int value)
{
    double z_value = ui->z_slider->value();
    ui->widget->set_z_rotate(z_value);  // заменить на move ?
}


// bonus part 1 ++++

void MainWindow::on_central_clicked()
{
    ui->widget->proec = 0;
    ui->widget->update();
}


void MainWindow::on_parallel_clicked()
{
    ui->widget->proec = 1;
    ui->widget->update();
}

// background edit
void MainWindow::on_setBgColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue).toRgb();
    ui->widget->bg_R = color.red();
    ui->widget->bg_G = color.green();
    ui->widget->bg_B = color.blue();
    ui->widget->bg_A = color.alpha();
    ui->widget->update();
}

// line edit
void MainWindow::on_line_type_activated(int index)
{
    ui->widget->line_style = index;
    ui->widget->update();
}

void MainWindow::on_lineWidth_slider_valueChanged(int value)
{
    ui->widget->line_width = (ui->lineWidth_slider->value()) / 10.0;
    ui->widget->update();
}

void MainWindow::on_setLineColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue).toRgb();
    ui->widget->line_R = color.red();
    ui->widget->line_G = color.green();
    ui->widget->line_B = color.blue();
    ui->widget->line_A = color.alpha();
    ui->widget->update();
}

void MainWindow::on_pointSize_slider_valueChanged(int value)
{
    ui->widget->point_size = (ui->pointSize_slider->value()) / 10.0;
    ui->widget->update();
}

void MainWindow::on_vertex_type_activated(int index)
{
    ui->widget->vertex_style = index;
    ui->widget->update();
}

void MainWindow::on_setVertColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue).toRgb();
    ui->widget->ver_R = color.red();
    ui->widget->ver_G = color.green();
    ui->widget->ver_B = color.blue();
    ui->widget->ver_A = color.alpha();
    ui->widget->update();
}

// save/load Settings

void MainWindow::on_saveSettigs_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Save settings info");
    msgBox.setText("The current program settings have been successfully saved "  + directory + "/3DViewerV1_config/settings.conf");
    msgBox.exec();
    ui->widget->save_settings();
}

void MainWindow::on_loadSettings_clicked() // добавить активацию актуальной проекции
{
    ui->widget->load_settings();
    if (ui->widget->proec) {
      ui->parallel->setChecked(true);
    } else {
      ui->central->setChecked(true);
    }
    ui->line_type->setCurrentIndex(ui->widget->line_style);
    ui->vertex_type->setCurrentIndex(ui->widget->vertex_style);
    ui->lineWidth_slider->setValue((int(ui->widget->line_width)) * 10); // потомушто
    ui->pointSize_slider->setValue((int(ui->widget->point_size)) * 10);
    ui->widget->update();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Load settings info");
    msgBox.setText("The last saved settings have been loaded successfully");
    msgBox.exec();
}


void MainWindow::on_radio_bmp_clicked()
{
    ui->widget->img_type = 1;
    ui->widget->update();
}


void MainWindow::on_radio_jpg_clicked()
{
    ui->widget->img_type = 2;
    ui->widget->update();
}


void MainWindow::on_save_button_clicked()
{
//    QString directory;  // вынесла в mainwindow.h
    QString filename;

    if (ui->widget->img_type == 1)
    {
      filename  = "/bmp_screen.bmp";
    }
    if (ui->widget->img_type == 2)
    {
      filename = "/jpg_screen.jpg";
    }
    QString filePath = directory + filename;
    ui->widget->saveScreen(ui->widget, filePath, ui->widget->img_type);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Screen");
    msgBox.setText("Screen saved successfully: " + filePath);
    msgBox.exec();
}


