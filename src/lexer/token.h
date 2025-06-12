#ifndef CALCULATOR_LEXER_TOKEN_H_
#define CALCULATOR_LEXER_TOKEN_H_

#include "../utils/stringBuffer.h"
#include <stddef.h>

// token
typedef enum {
  Integer,  // 123
  Operator, // +

  LParen, // (
  RParen, // )
} tokenType;

typedef struct {
  stringBuffer value;
  tokenType tty;
} token;

const char *token_display(token *tok);

// buffer

typedef struct {
  size_t capacity;
  size_t len;
  token *ptr;
} tokensBuffer;

tokensBuffer token_newBuffer();
void token_freeBuffer(tokensBuffer *buf);

void token_pushBuffer(tokensBuffer *buf, token tok);
token *token_peekBuffer(tokensBuffer *buf, size_t position);

#endif
