#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "error.h"
#include "scanner.h"
#include "parser.h"
#include "defaults.h"
#include "defaults.c"

int error_count = 0;
log_t *error_log;
log_t *log_focus;
FILE *SOURCE_FILE;

int main(int argc, char *argv[]) {

  // Check for file existence.
  SOURCE_FILE = fopen(argv[1], "r");
  if (!SOURCE_FILE) {
    printf("File not found.\n");
    exit(1);
  }

  // Pull parse table parse_table into memory.
  FILE *pt = fopen("parse-table.csv", "r");
  int c;
  char ***parse_table = malloc(NUM_COLS * sizeof(char **));
  for (int i = 0; i < NUM_COLS; i++) {
    parse_table[i] = malloc(NUM_ROWS * sizeof(char **));
  }
  int current_col = 0;
  int current_row = 0;

  if (pt) {
    int buffer_index = 0;
    char *buffer = calloc(MAX_CELL_SIZE, sizeof(char));
    while ((c = getc(pt)) != EOF) {
      if (c == ',' || c == '\n') {
        parse_table[current_col][current_row] = buffer;
        if (c == ',') {
          current_col++;
        } else if (c == '\n') {
          current_col = 0;
          current_row++;
        }
        buffer_index = 0;
        buffer = calloc(MAX_CELL_SIZE, sizeof(char));
      } else {
        buffer[buffer_index] = c;
        buffer_index++;
      }
    }
    fclose(pt);
  } else {
    printf("Parse table not found.\n");
    exit(1);
  }

  start_parse(parse_table);

/*
  token_t *tok = get_token();
  if (tok->type == SPACE) {
    printf("yes");
  }
*/

  fclose(SOURCE_FILE);

  printf("\n\n");

  if (error_count == 1) {
    printf("Compilation failed. 1 error.\n");
    print_errors();
  } else if (error_count > 1) {
    printf("Compilation failed. %d errors.\n", error_count);
    print_errors();
  } else {
    printf("Compilation successful.\n");
  }

}
