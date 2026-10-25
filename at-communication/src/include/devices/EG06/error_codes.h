#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#define MAX_ERROR_LENGTH 128

#include "error_type.h"

extern struct ErrorEntry cme_errors[];
extern const int cme_errors_size;

extern struct ErrorEntry cms_errors[];
extern const int cms_errors_size;

#endif