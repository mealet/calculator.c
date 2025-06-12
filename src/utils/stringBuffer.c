#include <stdlib.h>
#include <string.h>

#include "stringBuffer.h"

stringBuffer strbuf_new() {
  char *ptr = (char *)malloc(sizeof(char));
  return (stringBuffer){.ptr = ptr, .len = 0, .capacity = 1};
}

stringBuffer strbuf_from(char *input) {
  size_t len = strlen(input);
  char *ptr = (char *)malloc(sizeof(char) * len);

  strcpy(ptr, input);
  return (stringBuffer){.ptr = ptr, .len = len, .capacity = len};
}

void strbuf_free(stringBuffer *buf) {
  if (buf && buf->ptr && buf->capacity > 0) {
    free(buf->ptr);

    buf->len = 0;
    buf->capacity = 0;
  }
}

void strbuf_push(stringBuffer *buf, char chr) {
  buf->len += 1;

  if (buf->len > buf->capacity) {
    buf->capacity = buf->len;

    char *ptr = (char *)realloc(buf->ptr, sizeof(char) * buf->capacity);

    while (!ptr) {
      ptr = (char *)realloc(buf->ptr, sizeof(char) * buf->capacity);
    }

    buf->ptr = ptr;
  }

  buf->ptr[buf->len - 1] = chr;
}

char *strbuf_get(stringBuffer *buf) { return buf->ptr; }

char strbuf_getc(stringBuffer *buf, size_t position) {
  if (position >= buf->len) {
    return '\0';
  }

  return buf->ptr[position];
}
