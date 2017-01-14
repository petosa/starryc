#ifndef TYPE_H_
#define TYPE_H_

typedef enum {
    SPACE,
    PLUS,
    STAR,
    DOT,
    COMMA,
    PRIME,
    GRAVE,
    NL,
    END
} token_type_t;

typedef struct token {
  token_type_t type;
} token_t;

typedef struct log {
  char *data;
  struct log *next;
} log_t;

#endif
