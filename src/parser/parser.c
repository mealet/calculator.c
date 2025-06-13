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

astNode expression(parser *parser) {
  astNode node = term(parser);
  token *cur = current_token(parser);

  if (parser->is_eof) {
    return node;
  }

  if (node.type == None) {
    return node;
  }

  switch (cur->tty) {
  case Operator: {
    char operand = strbuf_getc(&cur->value, 0);
    next_token(parser);

    astNode *lhs = (astNode *)malloc(sizeof(astNode));
    *lhs = node;

    astNode *rhs = (astNode *)malloc(sizeof(astNode));
    *rhs = expression(parser);

    if (rhs->type == None) {
      fprintf(stderr, "Wrong expression provided\n");

      cleanup_ast(lhs);
      cleanup_ast(rhs);

      free(lhs);
      free(rhs);
    } else {

      if ((operand == '*' || operand == '/') && (rhs->type == Binary)) {
        astNode *new_node = rhs;
        astNode *old_lhs = lhs;

        astNode *rhs_new = new_node->lhs;

        astNode *priority_node = (astNode *)malloc(sizeof(astNode));
        *priority_node = (astNode){
            .type = Binary, .operand = operand, .lhs = old_lhs, .rhs = rhs_new};

        node = (astNode){.type = Binary,
                         .operand = new_node->operand,
                         .lhs = priority_node,
                         .rhs = rhs_new};
      } else {
        node = (astNode){
            .type = Binary, .operand = operand, .lhs = lhs, .rhs = rhs};
      }
    }
  } break;

  case RParen: {
    return node;
  } break;

  default: {
    fprintf(stderr, "Undefined token in expression found: %s\n",
            token_display(cur));
    next_token(parser);

    node = (astNode){.type = None};
  } break;
  }

  return node;
}

astNode term(parser *parser) {
  token *cur = current_token(parser);

  astNode node = {.type = None};

  if (parser->is_eof) {
    return node;
  }

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
      next_token(parser);
    } else {
      fprintf(stderr, "Unary operations only allowed with minus `-`\n");
      next_token(parser);
    }
  } break;

  case LParen: {
    cur = next_token(parser);

    if (cur->tty == RParen) {
      fprintf(stderr, "Empty parentheses found");
      next_token(parser);
    } else {
      astNode *expr = (astNode *)malloc(sizeof(astNode));
      *expr = expression(parser);

      node = (astNode){.type = Paren, .lhs = expr};

      cur = current_token(parser);
      if (cur->tty == RParen) {
        next_token(parser);
      }
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

  case Paren: {
    if (ast->lhs)
      free(ast->lhs);
  } break;
  }
}

void debug_ast(astNode *ast) {
  switch (ast->type) {
  case Number: {
    printf("NUMBER: %d\n", ast->integer);
  } break;

  case None: {
    printf("NONE\n");
  } break;

  case Unary: {
    printf("UNARY `%c`\n\n", ast->operand);
    debug_ast(ast->lhs);
    printf("\nUNARY END\n");
  } break;

  case Binary: {
    printf("BINARY `%c`\n", ast->operand);

    printf("\nLHS:\n");
    debug_ast(ast->lhs);

    printf("\nRHS:\n");
    debug_ast(ast->rhs);

    printf("\nBINARY END\n");
  }

  case Paren: {
    printf("-- PAREN START --\n\n");

    debug_ast(ast->lhs);

    printf("\n\n-- PAREN END --\n");
  } break;
  }
}
