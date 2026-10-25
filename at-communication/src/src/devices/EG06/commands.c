#include "command_defs.h"
#include "devices/EG06/error_codes.h"
#include "devices/initialization.h"
#include "parser_utils.h"
#include "devices/EG06/commands.h"

void EG06_initialise_commands(){
    get_band = &EG06_get_band;
    get_imei = &EG06_get_imei;
    get_modem_info = &EG06_get_modem_info;
    // get_number = &EG06_get_number;
    get_operator = &EG06_get_operator;
    get_operators = &EG06_get_operators;
    get_temperature = &EG06_get_temperature;
    get_service_cells = &EG06_get_service_cells;
    get_neighbour_cells = &EG06_get_neighbour_cells;
    send_message = &EG06_send_message;
    list_messages = &EG06_list_messages;

    cms_errors_map = cms_errors;
    cms_size = cms_errors_size;
    cme_errors_map = cme_errors;
    cme_size = cme_errors_size;
}