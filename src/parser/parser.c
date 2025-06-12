#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/stringBuffer.h"
#include "parser.h"

// main

parser parser_new(tokensBuffer tokens) {
  return (parser){.tokens = tokens,
                  .position = 0,
                  .current = token_peekBuffer(&tokens, 0),
                  .is_eof = false};
}

// TODO: Implement main parser function
astNode parser_parse(parser *parser);

// tech

token *next_token(parser *parser) {
  parser->position += 1;

  if (parser->position >= parser->tokens.len) {
    parser->is_eof = true;
    return NULL;
  }

  return token_peekBuffer(&parser->tokens, parser->position);
}

token *current_token(parser *parser) {
  if (parser->position >= parser->tokens.len) {
    parser->is_eof = true;
    return NULL;
  }

  return token_peekBuffer(&parser->tokens, parser->position);
}

// expressions

astNode term(parser *parser) {
  token *cur = current_token(parser);

  if (parser->is_eof) {
    return (astNode){};
  }

  astNode node = {.type = None};

  switch (cur->tty) {
  case Integer: {
    uint32_t value = atoi(strbuf_get(&cur->value));
    node = (astNode){.type = Number, .integer = value};

    next_token(parser);
  } break;

  case Operator: {
    char operand = strbuf_getc(&cur->value, 0);

    if (operand == '-') {
      astNode *expr = malloc(sizeof(astNode));
      *expr = term(parser);

      node = (astNode){.type = Unary, operand = '-', .lhs = expr};
    } else {
      fprintf(stderr, "Unary operations only allowed with minus `-`");
      next_token(parser);
    }
  } break;

  default: {
    fprintf(stderr, "Unexpected token in term found: %s\n", token_display(cur));
    next_token(parser);
  } break;
  };

  return node;
}

// cleanup

void cleanup_ast(astNode *ast) {
  switch (ast->type) {
  case Number:
  case None:
    break;

  case Unary: {
    if (ast->lhs)
      free(ast->lhs);
  } break;

  case Binary: {
    if (ast->lhs)
      free(ast->lhs);

    if (ast->rhs)
      free(ast->rhs);
  } break;
  }
}
