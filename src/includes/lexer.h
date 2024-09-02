#ifndef F13_LEXER_H
#define F13_LEXER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
    TOKEN__INVALID,
} TokenType;

typedef struct {
    char *buffer;
    char ch;
    uint64_t i;
    struct {
        size_t x, y;
    } location;
    struct {
        size_t len;
        TokenType *data;
    } tokens;
} Lexer;

Lexer Lexer__new();
void Lexer__scan(Lexer *lexer, const char *path);
void Lexer__next(Lexer *lexer);
bool Lexer__is_whitespace(char ch);
TokenType Lexer__identify(char ch);
void Lexer__add_token(Lexer *lexer, TokenType token);
void Lexer__release(Lexer *lexer);

#endif
