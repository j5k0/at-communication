#include "error_type.h"
#include "parser_utils.h"
#include "output_utils.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

struct ErrorEntry *cme_errors_map;
int cme_size;
struct ErrorEntry *cms_errors_map;
int cms_size;

static size_t contains(char separator, char *separators){
    size_t limit = strlen(separators);
    for(size_t i=0; i<limit; i++){
        if(separator == separators[i])
            return i;
    }
    return -1;
}

static int is_unsolicited(char *line){
    if(strncmp(line, "+CEREG: ", 8) == 0)
        return 1;
    if(strncmp(line, "+CMTI: ", 7) == 0)
        return 1;
    return 0;
}

int split_lines(char *buffer, char ***lineArray, int *count, int *offset){
    if((*lineArray)[*count] == NULL)
        (*lineArray)[*count] = calloc(MAX_LINE_LENGTH, sizeof(char));

    if((*lineArray)[*count] == NULL){
        print_error("Failed to allocate memory", "split_lines", -1);
        return PARSER_STATUS_ERROR;
    }

    int i=0;
    int length = strlen(buffer);
    while(buffer[i] != '\0'){
        // create memory for a response that is seperated by <CR><LF>
        if(buffer[i] == '\r' && buffer[i+1] == '\n'){
            (*lineArray)[*count][*offset] = '\0';
            if(is_unsolicited(((*lineArray)[*count])))
                continue;
            *count = *count + 1;
            if(i < length){
                (*lineArray)[*count] = calloc(MAX_LINE_LENGTH, sizeof(char));
                if((*lineArray)[*count] == NULL){
                    print_error("Failed to allocate memory", "split_lines", -1);
                    return PARSER_STATUS_ERROR;
                }
            }
            i = i + 2;
            *offset = 0;
            continue;
        }
        // read the inside of a separate response
        if(*offset < MAX_LINE_LENGTH - 1){
            (*lineArray)[*count][*offset] = buffer[i];
            *offset = *offset + 1;
        }
        i = i + 1;
    };

    return PARSER_STATUS_OK;
}

int seek_line(char **lines, int count, char *line){
    int len = strlen(line);
    for(int i=0; i<count; i++){
        if(strncmp(lines[i], line, len) == 0){
            return i;
        }
    }
    return -1;
}

int separate_groups(char *line, char ***groups, char delimiter, char *group_open, char *group_close, int *group_count){
    *group_count = 0;

    *groups = (char **)calloc(128, sizeof(char *));
    if(groups == NULL){
        print_error("Failed to allocate memory", "separate_groups", -1);
        return PARSER_STATUS_ERROR;
    }

    int capture_symbol = -1;
    int capture_depth = 0;

    char *group = calloc(MAX_LINE_LENGTH, sizeof(char));
    if(group == NULL){
        print_error("Failed to allocate memory", "separate_groups", -1);
        return PARSER_STATUS_ERROR;
    }

    int offset = 0;

    size_t limit = strlen(line);
    for(size_t i=0; i<limit; i++){
        if(line[i] == delimiter && capture_symbol == -1){
            (*groups)[*group_count] = group;
            *group_count = *group_count + 1;
            offset = 0;
            group = calloc(MAX_LINE_LENGTH, sizeof(char));
            if(group == NULL){
                print_error("Failed to allocate memory", "separate_groups", -1);
                return PARSER_STATUS_ERROR;
            }

            continue;
        }

        if(capture_symbol < 0){
            capture_symbol = contains(line[i], group_open); 
            if(capture_symbol > -1){
                capture_depth = 1;
                continue;
            }
        }
        else{
            if(group_close[capture_symbol] == line[i])
                capture_depth--;
            else if(group_open[capture_symbol] == line[i])
                capture_depth++;
            if(capture_depth == 0){
                capture_symbol = -1;
                continue;
            }
        }

        group[offset++] = line[i];
    }
    (*groups)[*group_count] = group;
    *group_count = *group_count + 1;
    return PARSER_STATUS_OK;
}

void free_lines(char **lines, int count){
    if(lines == NULL)
        return;
    for(int i=0; i<count; i++)
        if(lines[i] != NULL)
            free(lines[i]);
    free(lines);
}