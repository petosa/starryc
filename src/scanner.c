#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "global.h"
#include "error.h"

extern token_t * get_token() {
  int MAX_ERROR_SIZE = 256;
  char c = getc(SOURCE_FILE);
  char *message;

  int line_col = 0;
  int line_row = 0;

  token_t *token = malloc(sizeof(token_t));

  switch(c) {
    case ' ':
      token->type = SPACE;
      printf("SPACE");
    break;
    case '.':
      printf("DOT");
    break;
    case '+':
      printf("PLUS");
    break;
    case '*':
      printf("STAR");
    break;
    case ',':
      printf("COMMA");
    break;
    case '\'':
      printf("PRIME");
    break;
    case '`':
      printf("GRAVE");
    break;
    case '\n':
      line_row++;
      line_col = -1;
    break;
    default:
      message = malloc(sizeof(char) * MAX_ERROR_SIZE);
      sprintf(message, "lexical error: line %d column %d: invalid token (%c)", line_row, line_col, c);
      add_error(message);
    break;
  }
  line_col++;

  return token;

}
