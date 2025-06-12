#ifndef CALCULATOR_PARSER_PARSER_H_
#define CALCULATOR_PARSER_PARSER_H_

#include <stdbool.h>

#include "../lexer/token.h"
#include "../utils/stringBuffer.h"
#include "ast.h"

// parser
typedef struct {
  tokensBuffer tokens;

  size_t position;
  token *current;
  bool is_eof;
} parser;

parser parser_new(tokensBuffer tokens);
astNode parser_parse(parser *parser);

astNode expression(parser *parser);
astNode term(parser *parser);

#endif
