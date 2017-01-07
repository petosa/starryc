#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main(int argc, char *argv[]) {

  // Check for file existence.
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    printf("File not found.\n");
    exit(1);
  }

  // Pull parse table matrix into memory.
  FILE *parse_table = fopen("parse-table.csv", "r");
  int c;
  char **matrix = malloc(NUM_ROWS * sizeof(char **));
  char *row = malloc(NUM_ROWS * sizeof(char *));
  int current_col = 0;
  int current_row = 0;

  if (parse_table) {
    int buffer_index = 0;
    char *buffer = calloc(MAX_CELL_SIZE, sizeof(char));
    while ((c = getc(parse_table)) != EOF) {
      if (c == ',' || c == '\n') {
        printf("matrix[%d,%d] = %s\n", current_col, current_row, buffer);
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
    fclose(parse_table);
  } else {
    printf("Parse table not found.\n");
    exit(1);
  }

  // Scan through source file.
  while ((c = getc(file)) != EOF) {
    putchar(c);
  }
  fclose(file);
}
