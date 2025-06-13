#ifndef CALCULATOR_PARSER_AST_H_
#define CALCULATOR_PARSER_AST_H_

#include <stddef.h>
#include <stdint.h>

#include "../utils/stringBuffer.h"

// AST

typedef enum {
  Number,

  Unary,
  Binary,
  Paren,

  None
} exprType;

typedef struct Node {
  exprType type;

  uint32_t integer;
  char operand;

  struct Node *lhs;
  struct Node *rhs;
} astNode;

void cleanup_ast(astNode *ast);
void debug_ast(astNode *ast);

#endif
