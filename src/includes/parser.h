#ifndef F13_PARSER_H
#define F13_PARSER_H

#include "lexer.h"

typedef struct {
    Lexer *lexer;
} Parser;

Parser Parser__new(Lexer *lexer);
void Parser__run(Parser *parser);

#endif
