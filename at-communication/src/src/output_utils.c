#include <stdlib.h>

#include "argument_parser.h"
#include "json_utils.h"

void print_error(char *error_msg, char *type, int code){
    if(arguments.json){
        char * resp = format_error(error_msg, type, code);
        printf("%s\n", resp);
    }
    else{
        printf("Error:\n");
        printf("\tType: %s\n", type);
        printf("\tCode: %i\n", code);
        printf("\tMessage: %s\n", error_msg);
    }
}

void print_serving_cell(serving_cell_t *cell){
    if(arguments.json){

    }
    else{
        printf("Serving cell:\n");
        if(cell->mode == LTE_S_LTE){
            printf("\tLTE mode\n");
            printf("\tcellid: %s\n", cell->data.lte.cellid);
        }
        if(cell->mode == WCDMA_S_WCDMA){
            printf("\tWCDMA mode\n");
            printf("\tcellid: %s\n", cell->data.wcdma.cellid);
        }
    }
}

void print_neighbour_cells(neighbour_cell_t *cells, int count){
    if(arguments.json){

    }
    else{
        for(int i=0; i<count; i++){
            neighbour_cell_t c = cells[i];
            printf("Neighbour cell:\n");
            if(c.mode == LTE_N_INTER_LTE || c.mode == LTE_N_INTRA_LTE || c.mode == WCDMA_N_LTE){
                printf("\tLTE MODE\n");
                printf("\tearfcn %i\n", c.data.lte.earfcn);
            }
            if(c.mode == WCDMA_N_WCDMA || c.mode == LTE_N_WCDMA){
                printf("\tWCDMA MODE\n");
                printf("\tuarfcn: %i\n", c.data.wcdma.uarfcn);
            }
        }
    }
}

void print_bands(bands_t bands){
    if(arguments.json){
        char *resp = format_bands(bands);
        printf("%s\n", resp);
        free(resp);
    }
    else{
        printf("Bands:\n");
        printf("\tband: %s\n", bands.bandval);
        printf("\tlte band: %s\n", bands.ltebandval);
        printf("\ttds band: %s\n", bands.tdsbandval);
    }
}

void print_imei(char *imei){
    if(arguments.json){
        char *resp = format_imei(imei);
        printf("%s\n", resp);
        free(resp);
    }
    else{
        printf("IMEI: %s\n", imei);
    }
}

void print_info(modem_info_t info){
    if(arguments.json){
        char *resp = format_info(info);
        printf("%s\n", resp);
        free(resp);
    }
    else{
        printf("Model: %s\n", info.model);
        printf("Manufacturer: %s\n", info.manufacturer);
    }
}

void print_operator(operator_t op){
    if(arguments.json){
        char *resp = format_operator(op);
        printf("%s\n", resp);
        free(resp);
    }
    else{
        printf("Operator:\n");
        printf("\tMode: %i\n", op.mode);
        printf("\tAlphanumeric long: %s\n", op.alphanumeric_l);
        printf("\tAlphanumeric: %s\n", op.alphanumeric);
        printf("\tNumeric: %s\n", op.numeric);
        printf("\tAccess technology: %i\n", op.act);
    }
}

void print_operators(operator_t *ops, int count){
    if(arguments.json){
        char *resp = format_operators(ops, count);
        printf("%s\n", resp);
        free(resp);
    }
    else{
        printf("Operators:\n");
        for(int i=0; i<count; i++){
            printf("\tOperator:\n");
            printf("\t\tStatus: %i\n", ops[i].status);
            printf("\t\tMode: %i\n", ops[i].mode);
            printf("\t\tAlphanumeric long: %s\n", ops[i].alphanumeric_l);
            printf("\t\tAlphanumeric: %s\n", ops[i].alphanumeric);
            printf("\t\tNumeric: %s\n", ops[i].numeric);
            printf("\t\tAccess technology: %i\n", ops[i].act);
        }
    }
}

void print_temperature(temperatures_t temps){
    if(arguments.json){
        char *resp = format_temperatures(temps);
        printf("%s\n", resp);
        free(resp);
    }
    else{
        printf("Temperatures:\n");
        printf("\tXO temp: %iC\n", temps.xo_temp);
        printf("\tBB temp: %iC\n", temps.bb_temp);
        printf("\tPA temp: %iC\n", temps.pa_temp);
    }
}