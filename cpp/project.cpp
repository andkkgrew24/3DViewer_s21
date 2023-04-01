#include "project.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSettings>
#include <QUrl>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../viewer.h"
#ifdef __cplusplus
}
#endif

project::project(QWidget *parent)
    : QOpenGLWidget(parent)
{
  settings = new QSettings(QDir::homePath() + "/3DViewerV1_config/settings.conf", QSettings::IniFormat);
}

void project::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void project::resizeGL(int w, int h)
{
//    glViewport(0, 0, w, h);

}

void project::paintGL()
{
    glClearColor(bg_R / 255.0f, bg_G / 255.0f, bg_B / 255.0f, bg_A / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    proection(proec);
    glTranslated(0, 0, -2);
    draw();
}

void project::initObject(char *filename)
{
    start(filename, &obj);
    update();
}

void project::draw()
{
    glVertexPointer(3, GL_DOUBLE, 0, obj.matrix_object);
    glEnableClientState(GL_VERTEX_ARRAY);
    set_vertex_style(vertex_style);
    glColor4d(ver_R / 255.0f, ver_G / 255.0f, ver_B / 255.0f, ver_A / 255.0f);
    if (vertex_style != 2) {
      glPointSize(point_size);
      glDrawArrays(GL_POINTS, 0, obj.number_of_vertexes);
    }
    glLineWidth(line_width);
    glColor4d(line_R / 255.0f, line_G / 255.0f, line_B / 255.0f, line_A / 255.0f);
    set_line_style(line_style);
    glDrawElements(GL_LINES, obj.count_for_polygons, GL_UNSIGNED_INT, obj.polygons);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// base functions

void project::Scale_apply(double k)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    scale(A, rows, k);
    update();
}

void project::set_x_rotate(double x)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    rotate_x(A, rows, x);
    update();
}

void project::set_y_rotate(double y)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    rotate_y(A, rows, y);
    update();
}

void project::set_z_rotate(double z)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    rotate_z(A, rows, z);
    update();
}

void project::set_x_move(double x)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    transition(A, rows, 0, x);
    update();
}

void project::set_y_move(double y)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    transition(A, rows, 1, y);
    update();
}

void project::set_z_move(double z)
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    transition(A, rows, 2, z);
    update();
}

// ++++

void project::Transition_reset() // move to center
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    moveCentr(A, rows);
    update();
}

void project::Scale_reset() // optimaze scale
{
    double *A = obj.matrix_object;
    unsigned int rows = obj.number_of_vertexes;
    scaleReset(A, rows);
    update();
}


// bonus part +++

void project::proection(int proj) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (!proj) {
    glFrustum(-1, 1, -1, 1, 1, 99999);
  } else {
    glOrtho(-1, 1, -1, 1, -1, 99999);
  }
}

void project::set_vertex_style(int vertex_style)
{
  if (vertex_style == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (vertex_style == 0) {
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POINT);
  }
}

void project::set_line_style(int line_style)
{
    if (line_style == 0) {
      glDisable(GL_LINE_STIPPLE);
      glEnable(GL_LINE);
    } else if (line_style == 1) {
      glLineStipple(1, 0x00ff);
      glEnable(GL_LINE_STIPPLE);
    }

}

// Save/Load Settings
void project::save_settings()
{
    settings->setValue("line_style", line_style);
    settings->setValue("line_width", line_width);
    settings->setValue("vertex_style", vertex_style);
    settings->setValue("point_size", point_size);
    settings->setValue("proec", proec);
    settings->setValue("bg_R", bg_R);
    settings->setValue("bg_G", bg_G);
    settings->setValue("bg_B", bg_B);
    settings->setValue("bg_A", bg_A);
    settings->setValue("line_R", line_R);
    settings->setValue("line_G", line_G);
    settings->setValue("line_B", line_B);
    settings->setValue("line_A", line_A);
    settings->setValue("ver_R", ver_R);
    settings->setValue("ver_G", ver_G);
    settings->setValue("ver_B", ver_B);
    settings->setValue("ver_A", ver_A);
}

void project::load_settings()
{
    proec = settings->value("proec", proec).toInt();
    point_size = settings->value("point_size", point_size).toFloat();
    vertex_style = settings->value("vertex_style", 0).toInt();
    line_width = settings->value("line_width", 0).toFloat();
    line_style = settings->value("line_style", 0).toInt();
    bg_R = settings->value("bg_R", bg_R).toFloat();
    bg_G = settings->value("bg_G", bg_G).toFloat();
    bg_B = settings->value("bg_B", bg_B).toFloat();
    bg_A = settings->value("bg_A", bg_A).toFloat();
    ver_R = settings->value("ver_R", ver_R).toFloat();
    ver_G = settings->value("ver_G", ver_G).toFloat();
    ver_B = settings->value("ver_B", ver_B).toFloat();
    ver_A = settings->value("ver_A", ver_A).toFloat();
    line_R = settings->value("line_R", line_R).toFloat();
    line_G = settings->value("line_G", line_G).toFloat();
    line_B = settings->value("line_B", line_B).toFloat();
    line_A = settings->value("line_A", line_A).toFloat();
}

// screen

void project::saveScreen(project *screen, QString filePath, int img_type)
{
    QSize widgetSize = screen->size();
    int width = widgetSize.width();
    int height = widgetSize.height();

    QImage image(width, height, QImage::Format_RGBA8888);

    uchar* buf = new uchar[width*height*4];
    glReadPixels(370, 87, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buf);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * 4;
            image.setPixel(x, height - y - 1, qRgba(buf[i], buf[i+1], buf[i+2], buf[i+3]));
        }
    }

    if (img_type == 1)
    {
    image.save(filePath, "BMP");
    }
    else if (img_type == 2)
    {
    image.save(filePath, "JPEG");
    }

    delete [] buf;
}
