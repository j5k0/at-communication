#include "cJSON.h"
#include "types.h"
#include <stdio.h>

static void append_success(cJSON *object){
    cJSON_AddBoolToObject(object, "success", 1);
    cJSON_AddStringToObject(object, "msg", "");
}

char *format_error(char *error, char *type, int code){
    cJSON *response = cJSON_CreateObject();
    cJSON_AddBoolToObject(response, "success", 0);
    cJSON_AddNumberToObject(response, "code", code);
    cJSON_AddStringToObject(response, "type", type);
    cJSON_AddStringToObject(response, "msg", error);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}

char *format_imei(char *imei){
    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "imei", imei);

    cJSON *response = cJSON_CreateObject();
    cJSON_AddBoolToObject(response, "success", 1);
    cJSON_AddStringToObject(response, "msg", "");
    cJSON_AddItemToObject(response, "data", data);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}

char *format_info(modem_info_t info){
    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "model", info.model);
    cJSON_AddStringToObject(data, "manufacturer", info.manufacturer);

    cJSON *response = cJSON_CreateObject();
    cJSON_AddBoolToObject(response, "success", 1);
    cJSON_AddStringToObject(response, "msg", "");
    cJSON_AddItemToObject(response, "data", data);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}

char *format_operator(operator_t op){
    cJSON *data = cJSON_CreateObject();
    cJSON *operator = cJSON_CreateObject();

    cJSON_AddNumberToObject(operator, "mode", op.act);
    cJSON_AddItemToObject(data, "operator", operator);
    cJSON_AddStringToObject(operator, "alphanumeric long", op.alphanumeric_l);
    cJSON_AddStringToObject(operator, "alphanumeric", op.alphanumeric);
    cJSON_AddStringToObject(operator, "numeric", op.numeric);
    cJSON_AddNumberToObject(operator, "access technology", op.act);

    cJSON *response = cJSON_CreateObject();
    append_success(response);
    cJSON_AddItemToObject(response, "data", data);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}

char *format_operators(operator_t *ops, int count){
    cJSON *data = cJSON_CreateObject();
    cJSON *operator_array = cJSON_CreateArray();
    cJSON_AddItemToObject(data, "operators", operator_array);

    for(int i=0; i<count; i++){
        cJSON *entry = cJSON_CreateObject();
        cJSON_AddNumberToObject(entry, "status", ops[i].status);
        cJSON_AddNumberToObject(entry, "mode", ops[i].mode);
        cJSON_AddStringToObject(entry, "alphanumeric long", ops[i].alphanumeric_l);
        cJSON_AddStringToObject(entry, "alphanumeric", ops[i].alphanumeric);
        cJSON_AddStringToObject(entry, "numeric", ops[i].numeric);
        cJSON_AddNumberToObject(entry, "access technology", ops[i].act);
        cJSON_AddItemToArray(operator_array, entry);
    }

    cJSON *response = cJSON_CreateObject();
    append_success(response);
    cJSON_AddItemToObject(response, "data", data);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}

char *format_temperatures(temperatures_t temps){
    cJSON *data = cJSON_CreateObject();
    cJSON *temperature_table = cJSON_CreateObject();
    char num[8] = {0};

    cJSON_AddItemToObject(data, "temperatures", temperature_table);

    snprintf(num, 8, "%i", temps.xo_temp);
    cJSON_AddStringToObject(temperature_table, "XO temperature", num);
    snprintf(num, 8, "%i", temps.bb_temp);
    cJSON_AddStringToObject(temperature_table, "BB temperature", num);
    snprintf(num, 8, "%i", temps.pa_temp);
    cJSON_AddStringToObject(temperature_table, "PA temperature", num);

    cJSON *response = cJSON_CreateObject();
    append_success(response);
    cJSON_AddItemToObject(response, "data", data);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}

char *format_bands(bands_t bands){
    cJSON *data = cJSON_CreateObject();
    cJSON *bands_table = cJSON_CreateObject();

    cJSON_AddItemToObject(data, "bands", bands_table);
    cJSON_AddStringToObject(bands_table, "band", bands.bandval);
    cJSON_AddStringToObject(bands_table, "lte band", bands.ltebandval);
    cJSON_AddStringToObject(bands_table, "tds band", bands.tdsbandval);

    cJSON *response = cJSON_CreateObject();
    append_success(response);
    cJSON_AddItemToObject(response, "data", data);

    char *string = cJSON_Print(response);
    cJSON_Delete(response);
    return string;
}