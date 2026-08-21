#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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
    int c = getchar();
    return res == 3 && isspace(c);
}

#define BUFFERSIZE 100

int check_format_and_delete_whitespaces(char *s)
{
    int i, j;
    int count = 0;

    for (i = j = 0; s[i]; i++)
    {
        if (!isdigit(s[i]) && !isspace(s[i]) && tolower(s[i]) != 'x' && s[i] != '.' && s[i] != '^' && s[i] != '=' && s[i] != '+' && s[i] != '-')
            return 0;
        if (!isspace(s[i]))
            s[j++] = tolower(s[i]);
        if (s[i] == '=')
            count += 1;
    }
    s[j] = '\0';
    return count == 1;
}

void find_full_coeffs(char *s)
{
    int a = 0, b = 0, c = 0;
    char *peq = strstr(s, "=");
    assert(peq != NULL);

    size_t eq_ind = (size_t)(peq - s);
    size_t i = 0, j = 0;

    char *left = (char *)calloc(eq_ind + 1, sizeof(char));
    char *right = (char *)calloc(strlen(s) - eq_ind + 1, sizeof(char));

    for (i = 0; i < eq_ind; i++)
        left[i] = s[i];
    left[i++] = '\0';

    for (j = 0; s[i]; i++, j++)
    {
        right[j] = s[i];
    }
    right[j] = '\0';

    free(*left);
    free(*right);
}

void find_part_coeffs(char *s)
{
    char *p = NULL;
    size_t left = 0, right = 0;

    while ((p = strstr(s, "x^2")) != NULL)
    {
        left = right = (size_t)(p - s);
        while (left != 0 && s[left - 1] != 'x')
        {
            left--;
        }
    }
}

int parse_coeffs_from_equation(struct QuadraticEquation *equation)
{
    printf("Enter your equation:\n");
    printf("Format: ax^2 + bx + c = 0\n");
    // printf("Note: valid input may be ax^2 + bx + c = dx^2 + fx + g\n");
    printf("Your equation: ");

    float a = 0, b = 0, c = 0;

    char s[BUFFERSIZE];
    if (fgets(s, BUFFERSIZE, stdin) == NULL)
        return 0;
    char *ps = s;

    if (!check_format_and_delete_whitespaces(ps))
    {
        ungetc('\n', stdin); // для работы функции с циклом
        return 0;
    }

    find_coeffs(ps);

    return 1;
}
