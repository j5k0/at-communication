#include "parser_utils.h"
#include "command_utils.h"
#include "output_utils.h"
#include "devices/EG06/commands.h"

#include <string.h>

int EG06_get_imei(){
    int n = 0;
    char **lines = NULL;
    int status = query_command("AT+GSN", 500, 3, &lines, &n);
    if(status != 0)
        goto cleanup;
    print_imei(lines[1]);

cleanup:
    free_lines(lines, n);
    return status;
}

int EG06_get_modem_info(){
    int n = 0;
    char **lines = NULL;
    int status = query_command("ATI", 500, 3, &lines, &n);
    if(status != 0)
        goto cleanup;
    modem_info_t info;
    strncpy(info.manufacturer, lines[1], sizeof(info.manufacturer));
    strncpy(info.model, lines[2], sizeof(info.model));
    print_info(info);

cleanup:
    free_lines(lines, n);
    return status;
}