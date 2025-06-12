#ifndef CALCULATOR_UTILS_INPUTBUFFER_H_
#define CALCULATOR_UTILS_INPUTBUFFER_H_

#include <stddef.h>

typedef struct {
  char *ptr;

  size_t len;
  size_t capacity;
} stringBuffer;

stringBuffer strbuf_new();
stringBuffer strbuf_from(char *input);

void strbuf_free(stringBuffer *buf);
void strbuf_push(stringBuffer *buf, char chr);

char strbuf_getc(stringBuffer *buf, size_t position);
char *strbuf_get(stringBuffer *buf);

#endif
