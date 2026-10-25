#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#define MAX_RESPONSE_LINES 128
#define MAX_LINE_LENGTH 512

#include "error_type.h"

enum ParserStatus{
    PARSER_STATUS_SEEKING,
    PARSER_STATUS_PARSING,
    PARSER_STATUS_DONE,
    PARSER_STATUS_ERROR,
    __PARSER_STATUS_MAX
};

void free_lines(char **lines, int count);
char** separate_fields_single(char *line, char delimiter, char *group_open, char *group_close, int *group_count);
void split_lines(char *buffer, char ***lineArray, int *count, int *offset);

extern struct ErrorEntry *cme_errors_map;
extern int cme_size;
extern struct ErrorEntry *cms_errors_map;
extern int cms_size;

#endif