#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include "types.h"

int get_serving_cell(char *line, serving_cell_t *cell);
int get_neighbour_cell_lte(char *line, neighbour_cell_t *cell);
int get_neighbour_cell_wcdma(char *line, neighbour_cell_t *cell);

#endif