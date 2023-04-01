#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>  // ui
#include <QColorDialog>  // bonus part - colors
#include <QSettings> // save settings
#include <QMessageBox> //  всплывающее инфо окно

// screen
#include <QImage>
#include <QOpenGLWidget>
#include <QScreen>

#include "project.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString directory = QDir::homePath();


private slots:

// minimum
    void on_open_button_clicked();

    void on_scale_apply_clicked();

    void on_x_rotate_clicked();
    void on_y_rotate_clicked();
    void on_z_rotate_clicked();

    void on_x_move_clicked();
    void on_y_move_clicked();
    void on_z_move_clicked();

// +++++++
    void on_transition_reset_clicked(); // move to center
    void on_scale_reset_clicked(); // normalize scale
    void on_y_slider_valueChanged(int value);
    void on_x_slider_valueChanged(int value);
    void on_z_slider_valueChanged(int value);

// bonus part +++

    void on_central_clicked();
    void on_parallel_clicked();

    void on_setBgColor_clicked();
    void on_setLineColor_clicked();
    void on_setVertColor_clicked();

    void on_pointSize_slider_valueChanged(int value);
    void on_lineWidth_slider_valueChanged(int value);

    void on_vertex_type_activated(int index);
    void on_line_type_activated(int index);

    void on_saveSettigs_clicked();
    void on_loadSettings_clicked();

    void on_radio_bmp_clicked();
    void on_radio_jpg_clicked();
    void on_save_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
