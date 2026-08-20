#include <stdio.h>
#include "solve_equation.h"

void get_coeffs_in_loop(struct QuadraticEquation *equation, int (*pfunction)(struct QuadraticEquation *equation))
{
    int parsing_status, c;

    while (1)
    {
        parsing_status = (*pfunction)(equation);
        if (parsing_status)
            return;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Enter correct coefficients!\n\n");
    }
}

int get_coeffs(struct QuadraticEquation *equation)
{
    printf("Enter coefficients\n");
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n");

    int res = scanf("%f %f %f", &equation->a, &equation->b, &equation->c);
    return res == 3;
}

int get_coeffs_from_equation(struct QuadraticEquation *equation)
{
    printf("Enter quadratic equation\n");
    printf("Format: [a]x2 + [b]x + [c] = 0\n");
    printf("Example: 2x2 + 10x + 7 = 0\n");

    int res = scanf("%fx2 + %fx + %f = 0", &equation->a, &equation->b, &equation->c);
    return res == 3;
}