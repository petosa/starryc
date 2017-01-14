#include <stdio.h>
#include "types.h"
#include "parser.h"
#include "scanner.h"
#include "error.h"

void start_parse(char *** parse_table) {
  if (parse_table) {
    token_t *tok = get_token();
    while (tok->type != END) {
      switch (tok->type) {
        case SPACE:
          printf("-%s-", parse_table[7][0]);
        break;
        case PLUS:
          printf("1");
        break;
        case STAR:
          printf("2");
        break;
        case DOT:
          printf("3");
        break;
        case COMMA:
          printf("4");
        break;
        case PRIME:
          printf("5");
        break;
        case GRAVE:
          printf("6");
        break;
        case NL:
          printf("7");
        break;
        case END:
          printf("8");
        break;
      }
      tok = get_token();
    }
  }
}
