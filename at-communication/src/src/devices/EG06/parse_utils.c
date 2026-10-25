#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "parser_utils.h"

int get_serving_cell(char *line, serving_cell_t *cell){
    if(strncmp(line, "+QENG: ", 7) != 0)
        return -1;

    int group_count;
    char **groups = separate_fields_single(line + strlen("+QENG: "), ',', "\"", "\"", &group_count);

    if(strcmp(groups[2], "LTE") == 0){
        cell->mode = LTE_S_LTE; 
        strncpy(cell->data.lte.state, groups[1], sizeof(cell->data.lte.state));
        strncpy(cell->data.lte.is_tdd, groups[3], sizeof(cell->data.lte.is_tdd));
        cell->data.lte.mcc = atoi(groups[4]);
        cell->data.lte.mnc = atoi(groups[5]);
        strncpy(cell->data.lte.cellid, groups[6], sizeof(cell->data.lte.cellid));
        strncpy(cell->data.lte.pcid, groups[7], sizeof(cell->data.lte.pcid));
        cell->data.lte.earfcn = atoi(groups[8]);
        strncpy(cell->data.lte.freq_band_ind, groups[9], sizeof(cell->data.lte.freq_band_ind));
        cell->data.lte.ul_bandwidth = atoi(groups[10]);
        cell->data.lte.dl_bandwidth = atoi(groups[11]);
        strncpy(cell->data.lte.tac, groups[12], sizeof(cell->data.lte.tac));
        strncpy(cell->data.lte.rsrp, groups[13], sizeof(cell->data.lte.rsrp));
        strncpy(cell->data.lte.rsrq, groups[14], sizeof(cell->data.lte.rsrq));
        cell->data.lte.rssi = atoi(groups[15]);
        cell->data.lte.sinr = atoi(groups[16]);
        cell->data.lte.srxlev = atoi(groups[17]);

        free_lines(groups, group_count);
        return 0;
    }
    else{
        cell->mode = LTE_S_WCDMA;
        strncpy(cell->data.wcdma.state, groups[1], sizeof(cell->data.wcdma.state));
        cell->data.wcdma.mcc = atoi(groups[3]);
        cell->data.wcdma.mnc = atoi(groups[4]);
        strncpy(cell->data.wcdma.lac, groups[5], sizeof(cell->data.wcdma.lac));
        cell->data.wcdma.uarfcn = atoi(groups[6]);
        cell->data.wcdma.psc = atoi(groups[7]);
        cell->data.wcdma.rac = atoi(groups[8]);
        cell->data.wcdma.rscp = atoi(groups[9]);
        cell->data.wcdma.ecio = atoi(groups[10]);
        cell->data.wcdma.phych = atoi(groups[11]);
        cell->data.wcdma.sf = atoi(groups[12]);
        cell->data.wcdma.slot = atoi(groups[13]);
        strncpy(cell->data.wcdma.speech_code, groups[14], sizeof(cell->data.wcdma.speech_code));
        cell->data.wcdma.comMod = atoi(groups[15]);

        free_lines(groups, group_count);
        return 0;
    }
}

int get_neighbour_cell_lte(char *line, neighbour_cell_t *cell){
    if(strncmp(line, "+QENG: ", 7) != 0)
        return -1;

    int group_count;
    char **groups = separate_fields_single(line + strlen("+QENG: "), ',', "\"", "\"", &group_count);

    if(strcmp(groups[0], "neighbourcell intra") == 0){
        cell->mode = LTE_N_INTRA_LTE;
        cell->data.lte.earfcn = atoi(groups[2]);
        strncpy(cell->data.lte.pcid, groups[3], sizeof(cell->data.lte.pcid));
        strncpy(cell->data.lte.rsrq, groups[4], sizeof(cell->data.lte.rsrq));
        strncpy(cell->data.lte.rsrp, groups[5], sizeof(cell->data.lte.rsrp));
        cell->data.lte.rssi = atoi(groups[6]);
        cell->data.lte.sinr = atoi(groups[7]);
        cell->data.lte.srxlev = atoi(groups[8]);
        cell->data.lte.cell_resel_priority = atoi(groups[9]);
        strncpy(cell->data.lte.s_non_intra_search, groups[10], sizeof(cell->data.lte.s_non_intra_search));
        strncpy(cell->data.lte.thresh_serving_low, groups[11], sizeof(cell->data.lte.thresh_serving_low));
        strncpy(cell->data.lte.s_intra_search, groups[12], sizeof(cell->data.lte.s_intra_search));
        free_lines(groups, group_count);
        return 0;
    }

    if(strcmp(groups[0], "neighbourcell inter") == 0){
        cell->mode = LTE_N_INTER_LTE;
        cell->data.lte.earfcn = atoi(groups[2]);
        strncpy(cell->data.lte.pcid, groups[3], sizeof(cell->data.lte.pcid));
        strncpy(cell->data.lte.rsrq, groups[4], sizeof(cell->data.lte.rsrq));
        strncpy(cell->data.lte.rsrp, groups[5], sizeof(cell->data.lte.rsrp));
        cell->data.lte.rssi = atoi(groups[6]);
        cell->data.lte.sinr = atoi(groups[7]);
        cell->data.lte.srxlev = atoi(groups[8]);
        cell->data.lte.cell_resel_priority = atoi(groups[9]);
        strncpy(cell->data.lte.threshX_low, groups[10], sizeof(cell->data.lte.threshX_low));
        strncpy(cell->data.lte.threshX_high, groups[11], sizeof(cell->data.lte.threshX_high));
        free_lines(groups, group_count);
        return 0;
    }

    if(strcmp(groups[0], "neighbourcell") == 0){
        cell->mode = LTE_N_WCDMA;
        cell->data.wcdma.uarfcn = atoi(groups[2]);
        cell->data.wcdma.cell_resel_priority = atoi(groups[3]);
        strncpy(cell->data.wcdma.thresh_Xhigh, groups[4], sizeof(cell->data.wcdma.thresh_Xhigh));
        strncpy(cell->data.wcdma.thresh_Xlow, groups[5], sizeof(cell->data.wcdma.thresh_Xlow));
        cell->data.wcdma.psc = atoi(groups[6]);
        cell->data.wcdma.rscp = atoi(groups[7]);
        cell->data.wcdma.ecno = atoi(groups[8]);
        cell->data.wcdma.srxlev = atoi(groups[9]);
        free_lines(groups, group_count);
        return 0;
    }

    free_lines(groups, group_count);
    return -1;
}

int get_neighbour_cell_wcdma(char *line, neighbour_cell_t *cell){
    if(strncmp(line, "+QENG: ", 7) != 0)
        return -1;

    int group_count;
    char **groups = separate_fields_single(line + strlen("+QENG: "), ',', "\"", "\"", &group_count);

    if(strcmp(groups[1], "WCDMA") == 0){
        cell->mode = WCDMA_N_WCDMA;
        cell->data.wcdma.uarfcn = atoi(groups[2]);
        strncpy(cell->data.wcdma.srxqual, groups[3], sizeof(cell->data.wcdma.srxqual));
        cell->data.wcdma.psc = atoi(groups[4]);
        cell->data.wcdma.rscp = atoi(groups[5]);
        cell->data.wcdma.ecno = atoi(groups[6]);
        cell->data.wcdma.set = atoi(groups[7]);
        strncpy(cell->data.wcdma.rank, groups[8], sizeof(cell->data.wcdma.rank));
        cell->data.wcdma.srxlev = atoi(groups[9]);
        free_lines(groups, group_count);
        return 0;
    }

    if(strcmp(groups[1], "LTE") == 0){
        cell->mode = WCDMA_N_LTE;
        cell->data.lte.earfcn = atoi(groups[2]);
        strncpy(cell->data.lte.cellid, groups[3], sizeof(cell->data.lte.cellid));
        strncpy(cell->data.lte.rsrp, groups[4], sizeof(cell->data.lte.rsrp));
        strncpy(cell->data.lte.rsrq, groups[5], sizeof(cell->data.lte.rsrq));
        strncpy(cell->data.lte.s_rxlev, groups[6], sizeof(cell->data.lte.s_rxlev));
        free_lines(groups, group_count);
        return 0;
    }

    free_lines(groups, group_count);
    return -1;
}