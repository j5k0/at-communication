#include "argument_parser.h"
#include "command_defs.h"
#include "devices/initialization.h"
#include "modem_list.h"

#define CURRENT_DEVICE DEVICE_EG06

struct arguments arguments = { 0 };

int main(int argc, char **argv){
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    init_device_functions(CURRENT_DEVICE);

    if(arguments.band)
        get_band();

    if(arguments.service_cell)
        get_service_cells();

    if(arguments.imei)
        get_imei();

    if(arguments.info)
        get_modem_info();

    if(arguments.op)
        get_operator();

    if(arguments.ops)
        get_operators();

    if(arguments.message)
        send_message();

    if(arguments.messages)
        list_messages();

    if(arguments.number)
        get_number();

    if(arguments.neighbour)
        get_neighbour_cells();

    if(arguments.temperature)
        get_temperature();

    return 0;
}