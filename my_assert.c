#include "my_assert.h"
#include <stdio.h>
#include <stdlib.h>

void _myassert(int condition, const char *file, int line)
{
    if (!condition)
    {
        fprintf(stderr, "\x1b[31m"
                        "My asseration error: %s:%d\n"
                        "\x1b[0m",
                file, line);
        exit(1);
    }
}