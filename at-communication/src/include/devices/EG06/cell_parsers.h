#ifndef CELL_PARSERS_H
#define CELL_PARSERS_H

#include "types.h"

int get_serving_cell(char *line, serving_cell_t *cell);
int get_neighbour_cell_lte(char *line, neighbour_cell_t *cell);
int get_neighbour_cell_wcdma(char *line, neighbour_cell_t *cell);

#endif