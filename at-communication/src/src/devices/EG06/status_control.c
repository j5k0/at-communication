#include "parser_utils.h"
#include "command_utils.h"
#include "output_utils.h"
#include "devices/EG06/commands.h"

#include <string.h>

int EG06_get_band(){
    int n = 0, g = 0;
    char **lines = NULL, **groups = NULL;

    int status = query_command("AT+QCFG=\"band\"", 500, 3, &lines, &n);
    if(status != 0)
        goto cleanup;

    int start = seek_line(lines, n, "+QCFG: ");
    if(start < 0){
        print_error("Failed to find response line", "seek_line", -1);
        goto cleanup;
    }
    status = separate_groups(lines[start] + strlen("+QCFG: "), &groups, ',', "\"", "\"", &g);
    if(status < 0)
        goto cleanup;
    
    bands_t bands;
    strncpy(bands.bandval, groups[1], sizeof(bands.bandval));
    strncpy(bands.ltebandval, groups[2], sizeof(bands.ltebandval));
    strncpy(bands.tdsbandval, groups[3], sizeof(bands.tdsbandval));
    print_bands(bands);

cleanup:
    free_lines(lines, n);
    free_lines(groups, g);
    return 0;
}