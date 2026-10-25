#include "command_utils.h"
#include "parser_utils.h"
#include "serial_utils.h"
#include "output_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024*10

static int check_error(char *line){
    if(strncmp("ERROR", line, 5) == 0){
        print_error("Encountered an error", "Unknown", 0);
        return 1;
    }
    if(strncmp("+CME ERROR", line, 10) == 0){
        int error_code = atoi(line + strlen("+CME ERROR: "));
        char *error_string = translate_error_code(cme_errors_map, cme_size, error_code);
        print_error(error_string, "CME ERROR", error_code);
        return 1;
    }
    if(strncmp("+CMS ERROR", line, 10) == 0){
        int error_code = atoi(line + strlen("+CMS ERROR: "));
        char *error_string = translate_error_code(cms_errors_map, cms_size, error_code);
        print_error(error_string, "CMS ERROR", error_code);
        return 1;
    }
    return 0;
}

static int check_end_conditions(char **lines, int count){
    for(int i=0; i<count; i++){
        if(strncmp("OK", lines[i], strlen("OK")) == 0)
            return 1;
        if(check_error(lines[i]))
            return 2;
    }
    return 0;
}

int query_command(char *command, int timeout, int attempts, char ***response, int *lines){
    int ret = 0;
    int fd = serial_open("/dev/ttyUSB2");
    if(fd < 0){
        return 1;
    }
    for(int i=0; i<attempts; i++){
        ret = get_lines(fd, command, timeout, response, lines);
        if(ret == 1){
            serial_close(fd);
            return 0;
        }
        if(ret == 2){
            serial_close(fd);
            return 1;
        }
    }

    print_error("Timeout", "Unknown", -1);
    serial_close(fd);
    return 1;
}

int get_spec_lines(char *prefix, char **lines, int line_count, char ***spec_lines, int *spec_count){
    *spec_count = 0;
    *spec_lines = calloc(line_count, sizeof(char *));
    for(int i=0; i<line_count; i++){
        if(strncmp(lines[i], prefix, strlen(prefix)) == 0){
            *spec_lines[*spec_count] = lines[i];
            *spec_count = *spec_count + 1;
        }
    }
    return 0;
}

int get_lines(int fd, char *command, double timeout, char ***lines, int *line_count){
    int ret = 0;

    if((ret = serial_configure(fd)) != 0) return COMMAND_STATUS_ERROR;

    char terminated[strlen(command)+3];
    
    snprintf(terminated, strlen(command)+3, "%s\r\n", command);
    serial_write(fd, terminated);

    struct timespec start, end;
    double cpu_time;
    clock_gettime(CLOCK_MONOTONIC, &start);

    *lines = calloc(MAX_RESPONSE_LINES, sizeof(char *));
    int offset = 0;

    int run = 1;
    while(run){
        char *tmp = calloc(MAX_BUFFER_SIZE, sizeof(char));
        serial_read(fd, tmp, SERIAL_MAX_READ_BYTES);
        split_lines(tmp, lines, line_count, &offset);
        int status = check_end_conditions(*lines, *line_count);
        if(status != 0){
            free(tmp);
            return status;
        } 
        free(tmp);

        clock_gettime(CLOCK_MONOTONIC, &end);
        time_t seconds = end.tv_sec - start.tv_sec;
        time_t nanoseconds = end.tv_nsec - start.tv_nsec;
        cpu_time = seconds * 1000.0 + nanoseconds / 100000.0; // convert to milliseconds
        if(cpu_time > timeout)
            return COMMAND_STATUS_TIMEOUT;
    }

    return COMMAND_STATUS_OK;
}