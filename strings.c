#include "strings.h"
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "my_assert.h"

void print_phrase(const char *s)
{
    my_assert(s);

    printf("%s%s", YELLOW_C, ARROW_S);
    char c = 0;
    const double sleep_time = 0.02; // seconds

    for (int i = 0; (c = s[i]); i++)
    {
        putchar(c);
        if (ARGS.output_delay)
        {
            fflush(stdout);
            usleep((useconds_t)(1e6 * sleep_time)); // in microseconds
        }
    }
    printf("%s", RESET_C);
}