#include "includes/lexer.h"
#include "includes/parser.h"
#include <stdio.h>

int
main(void) {
    Lexer lexer = Lexer__new();
    Lexer__scan(&lexer, "test.json");

    Parser parser = Parser__new(&lexer);
    Parser__run(&parser);

    Lexer__release(&lexer);

    return 0;
}
