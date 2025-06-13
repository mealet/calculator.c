#include "lexer/lexer.h"
#include "lexer/token.h"

#include "parser/ast.h"
#include "parser/parser.h"

#include "utils/stringBuffer.h"

#include <stdio.h>

int main() {
  char *input = "2 * 2";

  __attribute__((cleanup(token_freeBuffer))) tokensBuffer tokens =
      lexer_tokenize(input);

  size_t i;
  for (i = 0; i < tokens.len; i++) {
    token *tok = token_peekBuffer(&tokens, i);
    printf("| `%s`: %s ", tok->value.ptr, token_display(tok));
  }
  printf("|\n\n");

  parser parser = parser_new(tokens);
  astNode expr = expression(&parser);

  debug_ast(&expr);

  cleanup_ast(&expr);

  return 0;
}
