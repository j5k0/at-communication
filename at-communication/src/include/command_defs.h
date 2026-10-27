#ifndef COMMAND_DEFS_H
#define COMMAND_DEFS_H

#include "modem_list.h"

extern int (*get_band)();
extern int (*get_modem_info)();
extern int (*get_operator)();
extern int (*get_imei)();
extern int (*get_temperature)();
extern int (*get_operators)();
extern int (*get_service_cells)();
extern int (*get_neighbour_cells)();

#endif