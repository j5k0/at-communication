#include "command_utils.h"
#include "serial_utils.h"
#include "argument_parser.h"
#include "devices/EG06/commands.h"
#include <signal.h>

#include <string.h>

int EG06_send_message(){
    int ret = 0;
    int fd = serial_open("/dev/ttyUSB2");
    if(fd < 0){
        return 1;
    }

    char command[128];
    snprintf(command, 128, "AT+CMGS=\"%s\"\r\n", arguments.message_number);

    serial_configure(fd);
    serial_write(fd, "AT+CMGF=1\r\n");
    serial_write(fd, command);

    char buff[128] = {0};
    char message[128*12] = {0};

    while(fgets(buff, 128, stdin) != NULL){
        if(strncmp("SEND\n", buff, strlen("SEND\n")) == 0){
            message[strlen(message)-1] = '\0';
            serial_write(fd, message);
            serial_write(fd, "\032");
            break;
        }
        if(strncmp("QUIT\n", buff, strlen("QUIT\n")) == 0){
            serial_write(fd, "\033");
            break;
        }
        strncat(message, buff, strlen(buff));
    }

    return 0;
}

int EG06_list_messages(){
    // int ret = 0;
    // int fd = serial_open("/dev/ttyUSB2");
    // if(fd < 0){
    //     return 1;
    // }

    // serial_configure(fd);
    // // serial_write(fd, "AT+CMGF=1\r\n");
    // serial_flush(fd);

    // int line_count = 0;
    // char **response_lines;
    // ret = get_lines(fd, "AT+CMGL=\"ALL\"", 1000, &response_lines, &line_count);

    // for(int i=0; i<line_count; i++){
    //     printf("%s\n", response_lines[i]);
    // }

    return 0;
}