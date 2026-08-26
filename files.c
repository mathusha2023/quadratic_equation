#include "files.h"
#include <stdio.h>
#include "config.h"

void filecopy(FILE *ifp, FILE *ofp)
{
    int c = 0;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

int print_file(const char *file_path, const char *color)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
        return 0;

    printf("%s", color);
    filecopy(file, stdout);
    printf("%s", RESET_C);
    return 1;
}
