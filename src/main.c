#include "lexer/lexer.h"
#include "lexer/token.h"

#include "parser/ast.h"
#include "parser/parser.h"

#include "interpreter/interpreter.h"

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 255
#define INPUT_ARROW "> "

int main() {
  // initializing empty input buffer
  char input[MAX_INPUT_LEN + 1];

  while (1) {
    // printing this arrow (idk how to call it)
    printf(INPUT_ARROW);
    fflush(stdout);

    // clearing buffer from previous iteration

    memset(input, 0, sizeof(input));

    // taking input
    if (fgets(input, sizeof(input), stdin)) {
      if (input[0] == '\0') {
        continue;
      }

      // removing new line ascii symbol

      input[strcspn(input, "\n")] = '\0';

      // exit option
      if (!strcmp(input, "exit")) {
        break;
      }

      // analyzing with lexer
      __attribute__((cleanup(token_freeBuffer))) tokensBuffer tokens =
          lexer_tokenize(input);

      // parsing with parser
      parser parser = parser_new(tokens);
      __attribute__((cleanup(cleanup_ast))) astNode expr =
          parser_parse(&parser);

      if (expr.type == None) {
        return 1;
      }

      // and then evaluating the result
      uint32_t result = interpreter_eval(&expr);
      printf("%d\n", result);
    }
  }

  return 0;
}
