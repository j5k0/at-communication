#include "error_type.h"

#include <string.h>

char *translate_error_code(struct ErrorEntry *error_map, int map_size, int code){
    for(int i=0; i<map_size; i++){
        if(code == error_map[i].code)
            return error_map[i].error;
    }
    return NULL;
}