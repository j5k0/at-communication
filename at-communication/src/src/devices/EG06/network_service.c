#include "parser_utils.h"
#include "command_utils.h"
#include "output_utils.h"
#include "devices/EG06/commands.h"
#include "devices/EG06/parse_utils.h"
#include "types.h"

#include <stdlib.h>
#include <string.h>

int EG06_get_service_cells(){
    int n = 0;
    char **lines = NULL;
    int status = query_command("AT+QENG=\"servingcell\"", 1000, 3, &lines, &n);
    if(status != 0)
        goto cleanup;

    serving_cell_t serving;
    get_serving_cell(lines[1], &serving);
    print_serving_cell(&serving);

cleanup:
    free_lines(lines, n);
    return status;
}

int EG06_get_neighbour_cells(){
    int n = 0, ret = 0;
    char **lines = NULL;
    neighbour_cell_t *cells = NULL;

    int status = query_command("AT+QENG=\"servingcell\"", 5000,3, &lines, &n);
    if(status != 0)
        goto cleanup;

    serving_cell_t service;
    int service_mode = get_serving_cell(lines[1], &service);

    free_lines(lines, n);
    lines = NULL;
    n = 0;

    status = query_command("AT+QENG=\"neighbourcell\"", 5000, 3, &lines, &n);
    if(status != 0)
        goto cleanup;

    int cells_c = 0;
    cells = calloc(n, sizeof(neighbour_cell_t));
    for(int i=0; i<n; i++){
        neighbour_cell_t tmp;
        if(service_mode == 0)
            ret = get_neighbour_cell_lte(lines[i], &tmp);
        else
            ret = get_neighbour_cell_wcdma(lines[i], &tmp);

        if(ret == 0) cells[cells_c++] = tmp;
    }

    print_neighbour_cells(cells, cells_c);

cleanup:
    free(cells);
    free_lines(lines, n);
    return status;
}

int EG06_get_operators(){
    int n = 0, g = 0;
    char **lines = NULL, **groups = NULL;
    operator_t *ops = NULL;
    int status = query_command("AT+COPS=?", 180*1000, 1, &lines, &n);
    if(status != 0)
        goto cleanup;

    groups = separate_fields_single(lines[1] + strlen("+COPS: "), ',', "\"(", "\")", &g);

    int operator_count = 0;
    for(int i=0; i<g && strlen(groups[i]) != 0; i++)
        operator_count++;

    ops = calloc(operator_count, sizeof(operator_t));

    for(int i=0; i<operator_count; i++){
        int subgroup_count = 0;
        char **subgroups = separate_fields_single(groups[i], ',', "\"", "\"", &subgroup_count);
        ops[i].status = atoi(subgroups[0]);
        strncpy(ops[i].alphanumeric_l, subgroups[1], sizeof(ops[i].alphanumeric_l));
        strncpy(ops[i].alphanumeric, subgroups[2], sizeof(ops[i].alphanumeric));
        ops[i].act = atoi(subgroups[3]);
        free_lines(subgroups, subgroup_count);
    }

    print_operators(ops, operator_count);

cleanup:
    free(ops);
    free_lines(lines, n);
    free_lines(groups, g);
    return status;
}

int EG06_get_operator(){
    int n = 0, g = 0;
    char **lines = NULL, **groups = NULL;
    int status = query_command("AT+COPS?", 500, 3, &lines, &n);
    if(status != 0)
        goto cleanup;

    groups = separate_fields_single(lines[1] + strlen("+COPS: "), ',', "\"(", "\")", &g);

    if(g > 1){
        operator_t op = { -1, -1, -1, "", "", "" };
        op.mode = atoi(groups[0]);
        int format = atoi(groups[1]);
        if(format == 0)
            strncpy(op.alphanumeric_l, groups[2], sizeof(op.alphanumeric_l));
        if(format == 1)
            strncpy(op.alphanumeric, groups[2], sizeof(op.alphanumeric));
        if(format == 2)
            strncpy(op.numeric, groups[2], sizeof(op.numeric));
        op.act = atoi(groups[3]);

        print_operator(op);
    }

cleanup:
    free_lines(lines, n);
    free_lines(groups, g);
    return 0;
}