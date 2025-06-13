#ifndef CALCULATOR_INTERPRETER_INTERPRETER_H
#define CALCULATOR_INTERPRETER_INTERPRETER_H

#include "../parser/ast.h"
#include <stdint.h>

uint32_t interpreter_eval(astNode *expr);

#endif
