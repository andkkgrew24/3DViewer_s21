#ifndef PROJECT_H
#define PROJECT_H

#pragma once

#include <QTimer>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QSettings>

// screen
#include <QImage>
#include <QOpenGLWidget>
#include <QScreen>
#include <QUrl>


#ifdef __cplusplus
extern "C"
{
#endif
#include "../viewer.h"
#ifdef __cplusplus
}
#endif

class project : public QOpenGLWidget
{
    Q_OBJECT

private :
    QSettings *settings;
    project *screen;

public:
    project(QWidget *parent = nullptr);

    struct data obj = {0};

// base widget functions

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initObject(char *filename);
    void draw();
    void converter(double *point_array);

 // transforms functions

    // minimum
    void Scale_apply(double k);

    void set_x_rotate(double x);
    void set_y_rotate(double y);
    void set_z_rotate(double z);

    void set_x_move(double x);
    void set_y_move(double y);
    void set_z_move(double z);

    // +++++
    void Transition_reset();
    void Scale_reset();

 // bonus part +++

    int proec = 0; // projection flag
    void proection(int flag);

    // background
    double bg_R = 200;
    double bg_G = 200;
    double bg_B = 200;
    double bg_A = 1;

    // Vertex style
    double ver_R = 0;
    double ver_G = 255;
    double ver_B = 0;
    double ver_A = 1;
    double point_size = 3;
    int vertex_style = 0;
    void set_vertex_style(int vertex_style);

    // Line style
    double line_R = 20;
    double line_G = 20;
    double line_B = 20;
    double line_A = 1;
    double line_width = 1;
    int line_style = 0;
    void set_line_style(int line_style);

    // Save Settings
    void save_settings();
    void load_settings();

    // Screen jpg/bmp
    int img_type = 2;
    void saveScreen(project *screen, QString filePath, int img_type);

};

#endif // PROJECT_H

