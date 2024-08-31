#ifndef F13_LEXER_H
#define F13_LEXER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char *buffer;
    char ch;
    uint64_t i;
} Lexer;

typedef enum {
    TOKEN__DIGIT,
    TOKEN__STRING,
    TOKEN__BOOLEAN,
    TOKEN__COMMA,
    TOKEN__COLON,
    TOKEN__QUOTATION_MARK,
    TOKEN__OPEN_BRACKET,
    TOKEN__CLOSE_BRACKET,
    TOKEN__OPEN_CURLY,
    TOKEN__CLOSE_CURLY,
    TOKEN__NULL,
} Token;

Lexer Lexer__new();
void Lexer__scan(Lexer *lexer, const char *path);
void Lexer__next(Lexer *lexer);
bool Lexer__is_whitespace(char ch);

#endif
