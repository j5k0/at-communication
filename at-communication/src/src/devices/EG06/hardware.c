#include "parser_utils.h"
#include "command_utils.h"
#include "output_utils.h"
#include "devices/EG06/commands.h"

#include <stdlib.h>
#include <string.h>

int EG06_get_temperature(){
    int g = 0, n = 0;
    char **lines = NULL, **groups = NULL;
    int status = query_command("AT+QTEMP", 1000, 3, &lines, &n);
    if(status != 0)
        goto cleanup;
    groups = separate_fields_single(lines[1] + strlen("+QTEMP: "), ',', "", "", &g);
    temperatures_t temps = { atoi(groups[0]), atoi(groups[1]), atoi(groups[2]) };
    print_temperature(temps);

cleanup:
    free_lines(groups, g);
    free_lines(lines, n);
    return status;
}