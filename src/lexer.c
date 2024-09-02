#include "includes/lexer.h"
#include "includes/ascii.h"
#include "includes/debug.h"
#include "includes/err.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
static const char *
Lexer__token_to_str(TokenType token) {
    const char *tokens[] = {
        [TOKEN__DIGIT] = "digit",
        [TOKEN__STRING] = "string",
        [TOKEN__BOOLEAN] = "boolean",
        [TOKEN__COMMA] = "comma",
        [TOKEN__COLON] = "colon",
        [TOKEN__QUOTATION_MARK] = "quotation mark",
        [TOKEN__OPEN_BRACKET] = "open bracket",
        [TOKEN__CLOSE_BRACKET] = "close bracket",
        [TOKEN__OPEN_CURLY] = "close curly",
        [TOKEN__CLOSE_CURLY] = "close curly",
        [TOKEN__NULL] = "null",
    };

    return tokens[token];
}
#endif  // DEBUG

Lexer
Lexer__new() {
    return (
        Lexer) {.buffer = NULL, .ch = '\0', .i = 0, .tokens = {.len = 0, .data = NULL}, .location = {.x = 1, .y = 1}};
}

void
Lexer__scan(Lexer *lexer, const char *filepath) {
    FILE *file = fopen(filepath, "r");

    if (!file) {
        panic("reading the file");
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    lexer->buffer = malloc(len + 1);

    if (!lexer->buffer) {
        fclose(file);
        panic("allocating memory");
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    fread(lexer->buffer, 1, len, file);
#pragma GCC diagnostic pop
    lexer->buffer[len] = '\0';
    fclose(file);

    lexer->ch = lexer->buffer[lexer->i];
    Lexer__next(lexer);
}

bool
Lexer__is_whitespace(char ch) {
    return ch == ASCII_SPACE || ch == ASCII_TAB;
}

void
Lexer__next(Lexer *lexer) {
    while (lexer->ch != '\0') {
        if (Lexer__is_whitespace(lexer->ch)) {
            lexer->i += 1;
            lexer->ch = lexer->buffer[lexer->i];
            lexer->location.x += 1;
            continue;
        }

        if (lexer->ch == ASCII_LINE_FEED) {
            lexer->i += 1;
            lexer->ch = lexer->buffer[lexer->i];
            lexer->location.y += 1;
            lexer->location.x = 1;
            continue;
        }

        TokenType token = Lexer__identify(lexer->ch);

        if (token == TOKEN__INVALID) {
            panic("invalid JSON file (%d:%d)", lexer->location.y, lexer->location.x);
        }

#ifdef DEBUG
        debug("%s (%zu, %zu)", Lexer__token_to_str(token), lexer->location.y, lexer->location.x);
#endif  // DEBUG

        Lexer__add_token(lexer, token);

        lexer->i += 1;
        lexer->ch = lexer->buffer[lexer->i];
        lexer->location.x += 1;
    }
}

void
Lexer__add_token(Lexer *lexer, TokenType token) {
    if (lexer->tokens.len == 0) {
        lexer->tokens.data = malloc(sizeof(TokenType));
        lexer->tokens.data[0] = token;
    } else {
        lexer->tokens.data = realloc(lexer->tokens.data, sizeof(TokenType) * (lexer->tokens.len + 1));
        lexer->tokens.data[lexer->tokens.len] = token;
    }

    lexer->tokens.len += 1;
}

TokenType
Lexer__identify(char ch) {
    if (ch == '{') {
        return TOKEN__OPEN_BRACKET;
    } else if (ch == '}') {
        return TOKEN__CLOSE_BRACKET;
    } else if ((ch >= '1' && ch <= '9') || ch == '-' || ch == '.') {
        return TOKEN__DIGIT;
    } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return TOKEN__STRING;
    } else if (ch == ',') {
        return TOKEN__COMMA;
    } else if (ch == ':') {
        return TOKEN__COLON;
    } else if (ch == true || ch == false) {
        return TOKEN__BOOLEAN;
    } else if (ch == '\"') {
        return TOKEN__QUOTATION_MARK;
    } else if (ch == '[') {
        return TOKEN__OPEN_CURLY;
    } else if (ch == ']') {
        return TOKEN__CLOSE_CURLY;
    }

    return TOKEN__INVALID;
}

void
Lexer__release(Lexer *lexer) {
    free(lexer->buffer);
    lexer->buffer = NULL;

    free(lexer->tokens.data);
    lexer->tokens.data = NULL;
}
