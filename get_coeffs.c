#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"
#include <stdlib.h>
#include <string.h>
#include "fsm_parser.h"

void get_coeffs_in_loop(struct QuadraticEquation *equation, int (*pfunction)(struct QuadraticEquation *equation))
{
    int parsing_status = 0, c = 0;

    while (1)
    {
        parsing_status = (*pfunction)(equation);
        if (parsing_status)
            return;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("%sEnter correct coefficients!\n\n%s", RED_C, RESET_C);
    }
}

int get_coeffs(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf("%sEnter coefficients\n", BLUE_C);
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n%s", RESET_C);

    int res = scanf("%lg %lg %lg", &equation->a, &equation->b, &equation->c);
    int c = getchar();
    return res == 3 && isspace(c);
}

int parse_coeffs_from_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf("%sEnter your equation:\n", BLUE_C);
    printf("Format: ax^2 + bx + c = 0\n");
    printf("Note: valid input may be ax^2 + bx + c = dx^2 + fx + g\n");
    printf("Your equation: %s", RESET_C);

    char s[BUFFERSIZE] = {};
    if (!fgets(s, BUFFERSIZE, stdin))
        return 0;

    struct FSMParser parser = init_fsmparser(s, equation);

    char *c = parser.parse(&parser);

    if (c)
    {
        int ind = (int)(c - s);
        printf("Incorrect input:\n");
        printf("%s", s);
        printf("%s%*c <- incorrect symbol\n%s", RED_C, ind + 1, '^', RESET_C);
        ungetc('\n', stdin);
    }
    return !c;
}