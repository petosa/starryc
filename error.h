#ifndef ERROR_H_
#define ERROR_H_

#include "types.h"

extern log_t *error_log;
extern log_t *log_focus;
extern int error_count;

extern void add_error(char *msg);
extern void print_errors();

#endif
