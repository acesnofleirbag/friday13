#include "includes/lexer.h"
#include "includes/err.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Lexer
Lexer__new() {
    return (Lexer) {
        .buffer = NULL,
        .ch = '\0',
        .i = 0,
    };
}

void
Lexer__scan(Lexer *lexer, const char *filepath) {
    FILE *file = fopen(filepath, "r");

    if (!file) {
        panic("error reading the file");
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    lexer->buffer = malloc(len + 1);

    if (!lexer->buffer) {
        fclose(file);
        panic("error allocating memory");
    }

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    fread(lexer->buffer, 1, len, file);
    #pragma GCC diagnostic pop
    lexer->buffer[len] = '\0';
    fclose(file);

    lexer->ch = lexer->buffer[lexer->i];
    Lexer__next(lexer);

    free(lexer->buffer);
}

bool
Lexer__is_whitespace(char ch) {
    return ch == '\20' || ch == '\t';
}

void
Lexer__next(Lexer *lexer) {
    while (lexer->ch != '\0') {
        if (Lexer__is_whitespace(lexer->ch)) {
            lexer->i += 1;
        }
    }
}
