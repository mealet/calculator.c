#include "lexer/lexer.h"
#include "lexer/token.h"
#include "utils/stringBuffer.h"

#include <stdio.h>

int main() {
  char *input = "1 + (1 * 2)";

  tokensBuffer tokens = lexer_tokenize(input);

  size_t i;
  for (i = 0; i < tokens.len; i++) {
    token *tok = token_peekBuffer(&tokens, i);
    printf("`%s`: %s\n", tok->value.ptr, token_display(tok));
  }

  return 0;
}
