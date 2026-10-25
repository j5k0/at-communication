#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H
#include <argp.h>

extern struct argp argp;
error_t parse_opt(int key, char *arg, struct argp_state *state);
extern struct arguments{
    int apn;
    int band;
    int service_cell;
    int device;
    char device_string[64];
    int imei;
    int info;
    int json;
    int mock;
    char mock_path[128];
    int message;
    char message_number[128];
    int messages;
    int number;
    int neighbour;
    int op;
    int ops;
    int signal;
    int status;
    int temperature;

    int debug;
}arguments;

#endif