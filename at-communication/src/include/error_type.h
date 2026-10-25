#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H

#define MAX_ERROR_LENGTH 128

struct ErrorEntry{
    int code;
    char error[MAX_ERROR_LENGTH];
};

char *translate_error_code(struct ErrorEntry *error_map, int map_size, int code);

#endif