#include <stddef.h>
#include <stdlib.h>

#include "token.h"

tokensBuffer token_newBuffer() {
  token *ptr = (token *)malloc(sizeof(token));

  while (!ptr) {
    ptr = (token *)malloc(sizeof(token));
  }

  return (tokensBuffer){.capacity = 1, .len = 0, ptr};
}

void token_freeBuffer(tokensBuffer *buf) {
  if (buf) {
    for (size_t i = 0; i < buf->len; i++) {
      token *tok = token_peekBuffer(buf, i);
      strbuf_free(&tok->value);
    }

    if (buf->ptr) {
      free(buf->ptr);
    }

    buf->capacity = 0;
    buf->len = 0;
  }
}

void token_pushBuffer(tokensBuffer *buf, token tok) {
  buf->len += 1;

  if (buf->len > buf->capacity) {
    buf->capacity += 1;

    token *ptr = (token *)realloc(buf->ptr, sizeof(token) * buf->capacity);

    while (!ptr) {
      ptr = (token *)realloc(buf->ptr, sizeof(token) * buf->capacity);
    }

    buf->ptr = ptr;
  }

  buf->ptr[buf->len - 1] = tok;
}

token *token_peekBuffer(tokensBuffer *buf, size_t position) {
  if (buf->capacity < 1 || position >= buf->len)
    return NULL;

  return &buf->ptr[position];
}
