#ifndef TYPES_H
#define TYPES_H

typedef struct{
    int status, mode, act;
    char alphanumeric_l[32], alphanumeric[32], numeric[32];
}operator_t;

typedef struct{
    char bandval[64], ltebandval[64], tdsbandval[64];
} bands_t;

typedef struct{
    char manufacturer[64];
    char model[64];
} modem_info_t;

typedef struct{
    int xo_temp, bb_temp, pa_temp;
} temperatures_t;

typedef enum {
    LTE_S_LTE, LTE_S_WCDMA, WCDMA_S_WCDMA, LTE_N_INTRA_LTE, LTE_N_INTER_LTE, LTE_N_WCDMA, WCDMA_N_WCDMA, WCDMA_N_LTE
} cell_mode_t;

typedef struct {
    char state[64], is_tdd[64], cellid[16], pcid[64], freq_band_ind[64], tac[64], rsrp[64], rsrq[64];
    int mcc, mnc, earfcn, ul_bandwidth, dl_bandwidth, rssi, sinr, srxlev;
} serving_lte_t;

typedef struct {
    char state[64], lac[16], cellid[16], speech_code[64];
    int mcc, mnc, uarfcn, psc, rac, rscp, ecio, phych, sf, slot, comMod;
} serving_wcdma_t;

typedef struct {
    char pcid[64], rsrq[64], rsrp[64], s_non_intra_search[64], 
        thresh_serving_low[64], s_intra_search[64], threshX_low[64], 
        threshX_high[64], s_rxlev[64], cellid[16];
    int earfcn, rssi, sinr, srxlev, cell_resel_priority;
} neighbour_lte_t;

typedef struct {
    char thresh_Xhigh[64], thresh_Xlow[64], srxqual[64], rank[64];
    int uarfcn, cell_resel_priority, psc, rscp, ecno, srxlev, set;
} neighbour_wcdma_t;

typedef struct {
    cell_mode_t mode;
    union {
        serving_lte_t lte;
        serving_wcdma_t wcdma;
    } data;
} serving_cell_t;

typedef struct{
    cell_mode_t mode;
    union{
        neighbour_lte_t lte;
        neighbour_wcdma_t wcdma;
    } data;
} neighbour_cell_t;

#endif