#include "phrases.h"
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

void say(const char *s)
{
    my_assert(s);

    if (!ARGS.speech)
        return;

    const char *command_start = "say -v Milena -r 190 \"";
    const char *command_end = "\" &";
    char *p = (char *)calloc(strlen(command_start) + strlen(s) + strlen(command_end) + 1, sizeof(char));
    if (!p)
    {
        printf("%sMEMORY ERROR BROO!!!!!!!\n%s", RED_C, RESET_C);
        return;
    }

    int i = 0, j = 0;

    for (i = 0; command_start[i]; i++)
        p[i] = command_start[i];
    for (j = 0; s[j]; i++, j++)
        p[i] = s[j];
    for (j = 0; command_end[j]; i++, j++)
        p[i] = command_end[j];
    p[i] = '\0';
    system(p);
    free(p);
}

void print_and_say_phrase(const char *s)
{
    my_assert(s);

    say(s);
    print_phrase(s);
}