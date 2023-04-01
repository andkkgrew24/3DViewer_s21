#include "viewer.h"

void transition(double *A, unsigned int rows, int axis, double a) {
  for (int i = 0 + axis; (unsigned)i < rows * 3; i += 3) A[i] += a;
}

void scale(double *A, unsigned int rows, double k) {
  if (k == 0.0) k = 1;
  for (int i = 0; (unsigned)i < rows * 3; i++) {
    A[i] *= k;
  }
}

int scaleReset(double *A, unsigned int rows) {
  int status = ERROR;
  double x = 0, y = 0, z = 0;
  double dMax = 0, scaleKf = 0;
  double massMinMax[6];

  searchMinMax(A, rows, massMinMax);
  x = massMinMax[1] - massMinMax[0];
  y = massMinMax[3] - massMinMax[2];
  z = massMinMax[5] - massMinMax[4];
  dMax = x;
  if (y > dMax) dMax = y;
  if (z > dMax) dMax = z;
  scaleKf = (0.8 + 0.8) / dMax;
  if (scaleKf) {
    scale(A, rows, scaleKf);
    status = CORRECT;
  }
  return status;
}

void rotate_x(double *massiv, unsigned int rows, double angle) {
  double angle_rad = (angle * M_PI) / 180;
  for (int i = 0; (unsigned)i < rows * 3; i += 3) {
    double y = massiv[i + 1];
    double z = massiv[i + 2];
    massiv[i + 1] = cos(angle_rad) * y - sin(angle_rad) * z;
    massiv[i + 2] = sin(angle_rad) * y + cos(angle_rad) * z;
  }
}

void rotate_y(double *massiv, unsigned int rows, double angle) {
  double angle_rad = (angle * M_PI) / 180;
  for (int i = 0; (unsigned)i < rows * 3; i += 3) {
    double x = massiv[i];
    double z = massiv[i + 2];
    massiv[i] = cos(angle_rad) * x + sin(angle_rad) * z;
    massiv[i + 2] = sin(angle_rad) * (-x) + cos(angle_rad) * z;
  }
}

void rotate_z(double *massiv, unsigned int rows, double angle) {
  double angle_rad = (angle * M_PI) / 180;
  for (int i = 0; (unsigned)i < rows * 3; i += 3) {
    double x = massiv[i];
    double y = massiv[i + 1];
    massiv[i] = cos(angle_rad) * x - sin(angle_rad) * y;
    massiv[i + 1] = sin(angle_rad) * x + cos(angle_rad) * y;
  }
}

void searchMinMax(double *A, unsigned int rows, double *massMinMax) {
  double minX = DBL_MAX;
  double minY = DBL_MAX;
  double minZ = DBL_MAX;
  double maxX = DBL_MIN;
  double maxY = DBL_MIN;
  double maxZ = DBL_MIN;

  for (int i = 0; (unsigned)i < rows * 3; i += 3) {
    if (A[i] < minX) minX = A[i];
    if (A[i + 1] < minY) minY = A[i + 1];
    if (A[i + 2] < minZ) minZ = A[i + 2];
    if (A[i] > maxX) maxX = A[i];
    if (A[i + 1] > maxY) maxY = A[i + 1];
    if (A[i + 2] > maxZ) maxZ = A[i + 2];
  }
  massMinMax[0] = minX;
  massMinMax[1] = maxX;
  massMinMax[2] = minY;
  massMinMax[3] = maxY;
  massMinMax[4] = minZ;
  massMinMax[5] = maxZ;
}

void moveCentr(double *massiv, unsigned int rows) {
  double massMinMax[6];

  searchMinMax(massiv, rows, massMinMax);
  double centrX = massMinMax[0] + (massMinMax[1] - massMinMax[0]) / 2;
  double centrY = massMinMax[2] + (massMinMax[3] - massMinMax[2]) / 2;
  double centrZ = massMinMax[4] + (massMinMax[5] - massMinMax[4]) / 2;
  for (int i = 0; (unsigned)i < rows * 3; i += 3) {
    massiv[i] -= centrX;
    massiv[i + 1] -= centrY;
    massiv[i + 2] -= centrZ;
  }
}
