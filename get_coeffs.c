#include "get_coeffs.h"
#include <stdio.h>
#include <ctype.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"
#include <stdlib.h>
#include <string.h>

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
    my_assert(equation != NULL);

    printf(BLUE_C "Enter coefficients\n");
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n" RESET_C);

    int res = scanf("%f %f %f", &equation->a, &equation->b, &equation->c);
    int c = getchar();
    return res == 3 && isspace(c);
}

int is_char_allowed(char c)
{
    size_t length = sizeof ALLOWED_CHARS / sizeof(char);
    for (size_t i = 0; i < length; i++)
    {
        if (c == ALLOWED_CHARS[i])
            return 1;
    }
    return 0;
}

int check_format_and_delete_whitespaces(char *s)
{
    int i = 0, j = 0;
    int count = 0;

    for (i = j = 0; s[i]; i++)
    {
        if (!is_char_allowed(s[i]))
            return 0;
        if (!isspace(s[i]))
            s[j++] = (char)tolower(s[i]);
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
    my_assert(peq != NULL);

    size_t eq_ind = (size_t)(peq - s);
    size_t i = 0, j = 0;

    char *left = (char *)calloc(eq_ind + 1, sizeof(char));
    char *right = (char *)calloc(strlen(s) - eq_ind + 1, sizeof(char));

    for (i = 0; i < eq_ind; i++)
        left[i] = s[i];
    left[i++] = '\0';

    for (j = 0; s[i]; i++, j++)
        right[j] = s[i];
    right[j] = '\0';

    // realisation

    free(left);
    free(right);
}

void find_part_coeffs(char *s)
{
    char *p = NULL;
    size_t left = 0, right = 0;

    double a = 0, b = 0, c = 0;

    while ((p = strstr(s, "x^2")) != NULL)
    {
        left = right = (size_t)(p - s);
        while (left != 0 && s[left - 1] != 'x')
        {
            left--;
        }
        if (right == 0)
            a += 1;
        else
        {
            // a += (float)strtod();
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

    char s[BUFFERSIZE] = {};
    if (fgets(s, BUFFERSIZE, stdin) == NULL)
        return 0;
    char *ps = s;

    if (!check_format_and_delete_whitespaces(ps))
    {
        ungetc('\n', stdin); // для работы функции с циклом
        return 0;
    }

    find_full_coeffs(ps);

    return 1;
}
