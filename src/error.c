#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void add_error(char *msg) {
  if (error_log == NULL) {
    error_log = malloc(sizeof(log_t));
    error_log->data = msg;
    error_log->next = NULL;
    log_focus = error_log;
    error_count = 1;
  } else {
    log_t *prev = log_focus;
    log_focus = log_focus->next;
    log_focus = malloc(sizeof(log_t));
    log_focus->data = msg;
    prev->next = log_focus;
    error_count++;
  }
}

void print_errors() {
  log_t *focus = error_log;
  while (focus) {
    printf("%s\n", focus->data);
    focus = focus->next;
  }
}
