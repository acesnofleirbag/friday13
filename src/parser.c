#include "includes/parser.h"
#include "includes/lexer.h"

Parser
Parser__new(Lexer *lexer) {
    return (Parser) {
        .lexer = lexer,
    };
}

void
Parser__run(Parser *parser) {
    (void) (parser);
}
