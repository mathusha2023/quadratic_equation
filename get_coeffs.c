#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"
#include <stdlib.h>
#include <string.h>
#include "parser.h"

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
        printf(RED_C "Enter correct coefficients!\n\n" RESET_C);
    }
}

int get_coeffs(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf(BLUE_C "Enter coefficients\n");
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n" RESET_C);

    int res = scanf("%lg %lg %lg", &equation->a, &equation->b, &equation->c);
    int c = getchar();
    return res == 3 && isspace(c);
}

int parse_coeffs_from_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf(BLUE_C "Enter your equation:\n");
    printf("Format: ax^2 + bx + c = 0\n");
    printf("Note: valid input may be ax^2 + bx + c = dx^2 + fx + g\n");
    printf("Your equation: " RESET_C);

    char s[BUFFERSIZE] = {};
    if (!fgets(s, BUFFERSIZE, stdin))
        return 0;

    struct Parser parser = init_parser(s);

    if (!parser.check_format(&parser))
    {
        ungetc('\n', stdin); // для работы функции get_coeffs_in_loop
        return 0;
    }

    return parser.parse(&parser, equation);
}