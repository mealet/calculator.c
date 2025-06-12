#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/stringBuffer.h"
#include "token.h"

char next_char(size_t *pos, stringBuffer *buf) {
  *pos += 1;
  return strbuf_getc(buf, *pos);
}

tokensBuffer lexer_tokenize(char *input) {
  tokensBuffer buf = token_newBuffer();
  stringBuffer inp = strbuf_from(input);

  size_t position = 0;
  char current = strbuf_getc(&inp, 0);

  while (current != '\0') {
    // whitespace
    if (current == ' ') {
      current = next_char(&position, &inp);
    }

    // integer
    if (current >= '0' && current <= '9') {
      stringBuffer value = strbuf_new();

      while (current >= '0' && current <= '9' && current != '\0') {
        strbuf_push(&value, current);
        current = next_char(&position, &inp);
      }

      token_pushBuffer(&buf, (token){.value = value, .tty = Integer});

      continue;
    }

    // operators
    if (current == '+' || current == '-' || current == '*' || current == '/') {
      stringBuffer value = strbuf_new();
      strbuf_push(&value, current);

      token_pushBuffer(&buf, (token){.value = value, .tty = Operator});
      current = next_char(&position, &inp);

      continue;
    }

    // parentheses
    if (current == '(' || current == ')') {

      stringBuffer value = strbuf_new();
      strbuf_push(&value, current);

      tokenType tty = current == '(' ? LParen : RParen;

      token_pushBuffer(&buf, (token){.value = value, .tty = tty});
      current = next_char(&position, &inp);

      continue;
    }

    fprintf(stderr, "Undefined character found: %c\n", current);
    exit(1);
  }

  return buf;
};
