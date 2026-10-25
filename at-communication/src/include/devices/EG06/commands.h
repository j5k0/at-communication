#ifndef EG06_COMMANDS_H
#define EG06_COMMANDS_H

#define COMMAND_ATTEMPTS 3

int EG06_error_test();
int EG06_get_band();
int EG06_get_imei();
int EG06_get_modem_info();
int EG06_get_number();
int EG06_get_operator();
int EG06_get_operators();
int EG06_get_temperature();
int EG06_get_service_cells();
int EG06_get_neighbour_cells();
int EG06_send_message();
int EG06_list_messages();

#endif