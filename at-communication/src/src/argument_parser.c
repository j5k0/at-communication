#include "argument_parser.h"

#include <string.h>

char doc[] = "AT Communication Tool";
char args_doc[] = "";

// Commented out options are yet to be implemented
struct argp_option options[] = {
    {"band", 'b', 0, 0, "Get mobile network frequency band", 0 },
    {"cell", 'c', 0, 0, "Get serving cell info", 0 },
    {"debug", 'D', 0, 0, "Run the program in debug mode (print inputs and outputs)", 0 },
    {"device", 'd', "DEVICE", 0, "Set the device to communicate with", 0 },
    {"imei", 'i', 0, 0, "Get the IMEI number", 0 },
    {"info", 'I', 0, 0, "Get model and manufacturer", 0 },
    {"json", 'j', 0, 0, "Format the output as JSON", 0 },
    {"mock", 'm', "PATH", 0, "Run the program in mock mode (read responses from a file)", 0 },
    {"number", 'n', 0, 0, "Get mobile number (if reachable)", 0 },
    {"neighbour", 'N', 0, 0, "Get neighbour cells", 0 },
    {"operator", 'o', 0, 0, "Get currently selected modem operator", 0 },
    {"operators", 'O', 0, 0, "Get currently available operators", 0 },
    {"temperature", 't', 0, 0, "Get modem temperature", 0 },
    { 0 }
};

error_t parse_opt(int key, char *arg, struct argp_state *state){
    (void)state;
    switch(key){
        case 'b':
            arguments.band = 1;
            break;
        case 'c':
            arguments.service_cell = 1;
            break;
        case 'D':
            arguments.debug = 1;
        case 'd':
            break;
        case 'i':
            arguments.imei = 1;
            break;
        case 'I':
            arguments.info = 1;
            break;
        case 'j':
            arguments.json = 1;
            break;
        case 'm':
            strncpy(arguments.mock_path, arg, 128);
            arguments.mock = 1;
            break;
        case 'n':
            arguments.number = 1;
            break;
        case 'N':
            arguments.neighbour = 1;
            break;
        case 'o':
            arguments.op = 1;
            break;
        case 'O':
            arguments.ops = 1;
            break;
        case 't':
            arguments.temperature = 1;
            break;
        case ARGP_KEY_END:
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

struct argp argp = {
    options, 
    parse_opt, 
    args_doc, 
    doc,
    NULL,
    NULL,
    NULL
};