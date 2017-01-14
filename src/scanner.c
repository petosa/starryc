#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "global.h"
#include "error.h"
#include "defaults.h"

extern token_t * get_token() {
  char c = getc(SOURCE_FILE);
  char *message;

  int line_col = 0;
  int line_row = 0;

  token_t *token = malloc(sizeof(token_t));

  switch(c) {
    case ' ':
      token->type = SPACE;
      printf("SPACE ");
    break;
    case '.':
      token->type = DOT;
      printf("DOT ");
    break;
    case '+':
      token->type = PLUS;
      printf("PLUS ");
    break;
    case '*':
      token->type = STAR;
      printf("STAR ");
    break;
    case ',':
      token->type = COMMA;
      printf("COMMA ");
    break;
    case '\'':
      token->type = PRIME;
      printf("PRIME ");
    break;
    case '`':
      token->type = GRAVE;
      printf("GRAVE ");
    break;
    case '\n':
      token->type = NL;
      line_row++;
      line_col = -1;
      printf("NL ");
    break;
    case -1:
      token->type = END;
      printf("EOF");
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
