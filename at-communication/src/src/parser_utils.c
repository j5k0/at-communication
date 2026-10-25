#include "error_type.h"
#include "parser_utils.h"

#include <stdlib.h>
#include <string.h>

struct ErrorEntry *cme_errors_map;
int cme_size;
struct ErrorEntry *cms_errors_map;
int cms_size;

void split_lines(char *buffer, char ***lineArray, int *count, int *offset){
    if((*lineArray)[*count] == NULL)
        (*lineArray)[*count] = calloc(MAX_LINE_LENGTH, sizeof(char));

    int i=0;
    int length = strlen(buffer);
    while(buffer[i] != '\0'){
        // create memory for a response that is seperated by <CR><LF>
        if(buffer[i] == '\r' && buffer[i+1] == '\n'){
            (*lineArray)[*count][*offset] = '\0';
            *count = *count + 1;
            i = i + 2;
            *offset = 0;
            if(i < length)
                (*lineArray)[*count] = calloc(MAX_LINE_LENGTH, sizeof(char));
            continue;
        }
        // read the inside of a separate response
        if(*offset < MAX_LINE_LENGTH - 1){
            (*lineArray)[*count][*offset] = buffer[i];
            *offset = *offset + 1;
        }
        i = i + 1;
    };
}

static size_t contains(char separator, char *separators){
    size_t limit = strlen(separators);
    for(size_t i=0; i<limit; i++){
        if(separator == separators[i])
            return i;
    }
    return -1;
}

char** separate_fields_single(char *line, char delimiter, char *group_open, char *group_close, int *group_count){
    *group_count = 0;

    char **groups = (char **)calloc(128, sizeof(char *));
    int capture_symbol = -1;
    int capture_depth = 0;

    char *group = calloc(MAX_LINE_LENGTH, sizeof(char));
    int offset = 0;

    size_t limit = strlen(line);
    for(size_t i=0; i<limit; i++){
        if(line[i] == delimiter && capture_symbol == -1){
            groups[*group_count] = group;
            *group_count = *group_count + 1;
            offset = 0;
            group = calloc(MAX_LINE_LENGTH, sizeof(char));
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
    groups[*group_count] = group;
    *group_count = *group_count + 1;
    return groups;
}

void free_lines(char **lines, int count){
    if(lines == NULL)
        return;
    for(int i=0; i<count; i++)
        if(lines[i] != NULL)
            free(lines[i]);
    free(lines);
}