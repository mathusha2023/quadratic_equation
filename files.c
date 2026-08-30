#include "files.h"
#include <stdio.h>
#include "config.h"
#include "my_assert.h"

void filecopy(FILE *ifp, FILE *ofp)
{
    my_assert(ifp);
    my_assert(ofp);

    int c = 0;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

int print_file(const char *file_path, const char *color)
{
    my_assert(file_path);
    my_assert(color);

    FILE *file = fopen(file_path, "r");
    if (!file)
        return 0;

    printf("%s", color);
    filecopy(file, stdout);
    printf("%s", RESET_C);
    fclose(file);
    return 1;
}

// нумерация с 0, печать без перевода строки
int print_n_file_string(const char *path, int n, int new_line)
{
    my_assert(path);

    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("%sFile not opened!%s\n", RED_C, RESET_C);
        return 0;
    }

    int i = 0;
    char buff[BUFFERSIZE] = {};
    for (i = 0; i <= n; i++)
    {
        if (!fgets(buff, BUFFERSIZE, file))
        {
            printf("%sCant get a string %d, aim string is %d %s\n", RED_C, i, n, RESET_C);
            fclose(file);
            return 0;
        }
    }
    if (!new_line && strlen(buff))
        buff[strlen(buff) - 1] = '\0';

    printf("%s", buff);
    fclose(file);
    return 1;
}
