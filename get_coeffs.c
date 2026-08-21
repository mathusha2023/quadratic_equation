#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include "my_assert.h"
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
    my_assert(equation != NULL);

    printf("Enter coefficients\n");
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n");

    int res = scanf("%f %f %f", &equation->a, &equation->b, &equation->c);
    int c = getchar();
    return res == 3 && isspace(c);
}
