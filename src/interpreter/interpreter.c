#include "interpreter.h"
#include <stdio.h>

uint32_t interpreter_eval(astNode *expr) {
  switch (expr->type) {
  case Number: {
    return expr->integer;
  } break;

  case Unary: {
    uint32_t result = interpreter_eval(expr->lhs);

    if (expr->operand == '-') {
      result *= -1;
    }

    return result;
  } break;

  case Binary: {
    uint32_t lhs = interpreter_eval(expr->lhs);
    uint32_t rhs = interpreter_eval(expr->rhs);

    if (expr->operand == '+') {
      return lhs + rhs;
    } else if (expr->operand == '-') {
      return lhs - rhs;
    } else if (expr->operand == '*') {
      return lhs * rhs;
    } else if (expr->operand == '/') {
      return lhs / rhs;
    } else {
      fprintf(stderr, "Unimplemented operator: %c\n", expr->operand);
      return 0;
    }
  } break;

  case Paren: {
    return interpreter_eval(expr->lhs);
  } break;
  case None: {
    return 0;
  } break;
    //
  }
}
