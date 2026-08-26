#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"
#include <stdlib.h>
#include <string.h>
#include "fsm_parser.h"
#include "strings.h"
#include "files.h"
#include <unistd.h>

static void print_phrase(const char *s)
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

void get_coeffs_in_loop(struct QuadraticEquation *equation)
{
    my_assert(equation);

    int parsing_status = 0;

    while (1)
    {
        parsing_status = pretty_parse_coeffs(equation);
        if (parsing_status)
            return;
    }
}

void print_logo(void)
{
    if (!print_file(START_F, BLUE_C))
        return;
    printf("\n\n\n");
}

void print_greeting(void)
{
    print_phrase(GREETING_S);
    printf("\n");
}

void print_boobs(int n_whitespaces)
{
    char boobs_arr[][9] = {
        " /\\_/\\ \n",
        "( o.o )\n",
        " > ^ < \n"};
    printf(RED_C);
    for (int i = 0; i < 3; i++)
        printf("%*c%s", n_whitespaces, ' ', boobs_arr[i]);
    printf(RESET_C);
}

int pretty_parse_coeffs(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf("%s%s%s", CYAN_C, ARROW_S, RESET_C);

    char s[BUFFERSIZE] = {};
    if (!fgets(s, BUFFERSIZE, stdin))
        return 0;

    struct FSMParser parser = init_fsmparser(s, equation);

    char *c = parser.parse(&parser);

    if (c)
    {
        int ind = (int)(c - s);
        print_boobs(ind + (int)strlen(ARROW_S) - 3);
        printf("\n");
        print_phrase(ERROR_S);
    }
    printf("\n");
    return !c;
}
