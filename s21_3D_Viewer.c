#include "viewer.h"

int start(char *filename, data *object) {
  int status = ERROR;
  if (!first_file_reading(filename, object)) {
    if (!create_matrix(object) && !create_facets(object)) {
      second_file_reading(filename, object);
      status = CORRECT;
    }
  }
  return status;
}

void clear_project(data *object) {
  if (object != NULL) {
    clear_facets(object);
    clear_matrix(object);
  }
}

int first_file_reading(char *filename, data *object) {
  int status = ERROR;
  int count_v = 0;
  int count_f = 0;
  int count_for_facets = 0;
  FILE *file;
  if ((file = fopen(filename, "r")) != NULL) {
    char str[1000] = {'\0'};
    while (fgets(str, 999, file)) {
      if (str[0] == 'v' && str[1] == ' ') {
        count_v += 1;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        counter_for_facets(str, &count_for_facets);
        count_f += 1;
      }
    }
    object->facets = count_f;
    object->number_of_vertexes = count_v;
    object->count_for_polygons = count_for_facets * 2;
    status = CORRECT;
    fclose(file);
  }
  return status;
}

void counter_for_facets(char *str, int *count) {
  int vertex_in_facet = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      if (str[i + 1] >= '0' && str[i + 1] <= '9') {
        vertex_in_facet++;
      }
    }
  }
  *count += vertex_in_facet;
}

int create_matrix(data *object) {
  int status = ERROR;
  int rows = object->number_of_vertexes;
  if (rows > 0) {
    object->matrix_object =
        (double *)calloc(object->number_of_vertexes * 3, sizeof(double));
    status = CORRECT;
  }
  return status;
}

int create_facets(data *object) {
  int status = ERROR;
  if (object->facets) {
    object->polygons = (int *)calloc(object->count_for_polygons, sizeof(int));
  }
  if (object->polygons != NULL) {
    status = CORRECT;
  }
  return status;
}

void second_file_reading(char *filename, data *object) {
  FILE *file;
  if ((file = fopen(filename, "r")) != NULL) {
    char str[100000] = {'\0'};
    int index = 0;
    int count_for_facets = 0;
    while (fgets(str, 100000, file)) {
      if (str[0] == 'v' && str[1] == ' ') {
        double numX = 0, numY = 0, numZ = 0;
        sscanf(str, "v %lf %lf %lf", &numX, &numY, &numZ);
        object->matrix_object[index] = numX;
        object->matrix_object[index + 1] = numY;
        object->matrix_object[index + 2] = numZ;
        index += 3;
        //        push_to_matrix(str, object, &count);
      }
      if (str[0] == 'f' && str[1] == ' ') {
        filling_vertexes_in_facet(object, str, &count_for_facets);
        count_for_facets++;
      }
    }
    fclose(file);
  }
}

void filling_vertexes_in_facet(data *object, char *str, int *count) {
  int space_counter = 0;
  int stop_flag = 0;
  int j = 0;
  int k = 0;
  char buffer[100] = {'\0'};
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ' && space_counter && !stop_flag) {
      if (str[i] == '/') {
        stop_flag++;
      } else {
        buffer[j] = str[i];
        j++;
      }
    }
    if (str[i] == ' ') {
      if (space_counter) {
        int value = 0;
        sscanf(buffer, "%d", &value);
        stop_flag = 0;
        value--;
        object->polygons[*count + k] = value;
        if (k) {
          k++;
          object->polygons[*count + k] = value;
        }
        k++;
        j = 0;
        clear_buffer(buffer);
      }
      space_counter++;
    }
  }
  int value = 0;
  sscanf(buffer, "%d", &value);
  value--;
  object->polygons[*count + k] = value;
  k++;
  object->polygons[*count + k] = value;
  k++;
  value = object->polygons[*count];
  object->polygons[*count + k] = value;
  *count += k;
}

void clear_buffer(char *buffer) {
  for (unsigned long i = 0; i < strlen(buffer); i++) {
    if (buffer[i] != '\0') {
      memset(buffer, 0, 100);
    } else {
      break;
    }
  }
}

void clear_matrix(data *object) {
  if (object->matrix_object != NULL) {
    free(object->matrix_object);
  }
}

void clear_facets(data *object) {
  if (object->polygons != NULL) {
    free(object->polygons);
  }
}
