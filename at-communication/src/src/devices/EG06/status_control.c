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

    groups = separate_fields_single(lines[1] + strlen("+QCFG: "), ',', "\"", "\"", &g);
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