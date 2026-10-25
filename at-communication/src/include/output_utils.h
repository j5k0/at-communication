#ifndef OUTPUT_UTILS_H
#define OUTPUT_UTILS_H

#include "types.h"

void print_error(char *error_msg, char *type, int code);
void print_serving_cell(serving_cell_t *cell);
void print_bands(bands_t bands);
void print_imei(char *imei);
void print_info(modem_info_t info);
void print_operator(operator_t op);
void print_operators(operator_t *ops, int count);
void print_temperature(temperatures_t temps);
void print_neighbour_cells(neighbour_cell_t *cells, int count);

#endif