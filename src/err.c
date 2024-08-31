#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void
panic(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);

    exit(1);
}
