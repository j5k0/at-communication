#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "types.h"

char *format_error(char *error, char *type, int code);
char *format_imei(char *imei);
char *format_info(modem_info_t info);
char *format_operator(operator_t op);
char *format_operators(operator_t *ops, int count);
char *format_temperatures(temperatures_t temps);
char *format_bands(bands_t bands);

#endif