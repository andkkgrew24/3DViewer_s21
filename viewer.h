#ifndef VIEWER_H_
#define VIEWER_H_
#pragma once

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 1
#define CORRECT 0
//#define M_PI 3.14159265358979323846

typedef struct data {
  unsigned int number_of_vertexes;
  unsigned int facets;
  double *matrix_object;
  int *polygons;
  int count_for_polygons;
} data;

int start(char *filename, data *object);
int first_file_reading(char *filename, data *object);
void counter_for_facets(char *str, int *count);
int create_matrix(data *object);
int create_facets(data *object);
void second_file_reading(char *filename, data *object);
void push_to_matrix(char *str, data *object, int *count);
void filling_vertexes_in_facet(data *object, char *str, int *count);
void clear_buffer(char *buffer);
void clear_matrix(data *object);
void clear_facets(data *object);
void clear_project(data *object);

void transition(double *massiv, unsigned int rows, int axis, double a);
void scale(double *massiv, unsigned int rows, double k);
int scaleReset(double *A, unsigned int rows);
void rotate_x(double *massiv, unsigned int rows, double angle);
void rotate_y(double *massiv, unsigned int rows, double angle);
void rotate_z(double *massiv, unsigned int rows, double angle);
void searchMinMax(double *massiv, unsigned int rows, double *B);
void moveCentr(double *massiv, unsigned int rows);

#endif  // VIEWER_H_
