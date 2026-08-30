#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"
#include <stdlib.h>
#include <string.h>
#include "fsm_parser.h"
#include "phrases.h"
#include "files.h"

void print_logo(void)
{
    if (!print_file(START_F, BLUE_C))
        return;
    printf("\n\n\n");
}

void print_greeting(void)
{
    print_and_say_phrase(GREETING_S);
    printf("\n");
}

/**
 * @brief Print boobs
 *
 * This function prints boobs - cat that show user where is wrong char in his input
 *
 * @param n_whitespaces number of whitespaces before boobs
 */
static void print_boobs(int n_whitespaces)
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

/**
 * @brief Pretty parse coeffs
 *
 * This function get coeffs from console and put them to equation.
 * If input is incorrect - print boobs
 *
 * @param equation
 * @return int
 */
static int pretty_parse_coeffs(struct QuadraticEquation *equation)
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
        print_and_say_phrase(ERROR_S);
    }
    printf("\n");
    return !c;
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