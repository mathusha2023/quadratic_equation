#include "parser.h"
#include <stdio.h>
#include <ctype.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"
#include <stdlib.h>
#include <string.h>

static int is_char_allowed(char c)
{
    size_t length = sizeof ALLOWED_CHARS / sizeof(char);
    for (size_t i = 0; i < length; i++)
    {
        if (c == ALLOWED_CHARS[i])
            return 1;
    }
    return 0;
}

static int has_disallow_sequences(char *s)
{
    const size_t length = sizeof DISALLOW_COMBINATIONS / sizeof(DISALLOW_COMBINATIONS[0]);
    size_t i = 0;

    for (i = 0; i < length; i++)
    {
        if (strstr(s, DISALLOW_COMBINATIONS[i]))
            return 1;
    }
    return 0;
}

static int check_format_and_delete_whitespaces(char *s)
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
    return count == 1 && !has_disallow_sequences(s);
}

// удаляет из строки символы с left включительно до right не включительно
static void delete_substr(char *s, size_t left, size_t right)
{
    size_t i = 0, j = 0;
    for (i = j = 0; s[i]; i++)
    {
        if (left <= i && i < right)
            continue;
        s[j++] = s[i];
    }
    s[j] = '\0';
}

static double str_sum(char *s)
{
    double sum = 0;
    while (*s)
        sum += strtod(s, &s);
    return sum;
}

static double find_one_coeff(char *s, const char *pat)
{
    double x = 0;
    char *p = NULL;
    size_t left = 0, right = 0;
    size_t delta = strlen(pat);

    while ((p = strstr(s, pat)))
    {
        left = right = (size_t)(p - s);
        while (left != 0 && s[left - 1] != 'x' && s[left] != '+' && s[left] != '-')
        {
            left--;
        }
        if (right == 0)
            x += 1;
        else if (right - left == 1 && s[left] == '+')
            x += 1;
        else if (right - left == 1 && s[left] == '-')
            x -= 1;
        else
            x += strtod(s + left, NULL);
        delete_substr(s, left, right + delta);
    }
    return x;
}

static void find_part_coeffs(char *s, double *pa, double *pb, double *pc)
{
    *pa = *pb = *pc = 0;

    *pa = find_one_coeff(s, "x^2");
    *pb = find_one_coeff(s, "x^1");
    *pc = find_one_coeff(s, "x^0");
    *pb += find_one_coeff(s, "x");

    // считаем с как сумму оставшихся чисел
    *pc += str_sum(s);
}

static int find_full_coeffs(char *s, struct QuadraticEquation *equation)
{
    double a1 = 0, b1 = 0, c1 = 0;
    double a2 = 0, b2 = 0, c2 = 0;
    char *peq = strstr(s, "=");
    my_assert(peq);

    size_t eq_ind = (size_t)(peq - s);
    size_t i = 0, j = 0;

    char *left = (char *)calloc(eq_ind + 1, sizeof(char));
    char *right = (char *)calloc(strlen(s) - eq_ind + 1, sizeof(char));

    if (!left || !right)
        return 0;

    for (i = 0; i < eq_ind; i++)
        left[i] = s[i];
    left[i++] = '\0';

    for (j = 0; s[i]; i++, j++)
        right[j] = s[i];
    right[j] = '\0';

    find_part_coeffs(left, &a1, &b1, &c1);
    find_part_coeffs(right, &a2, &b2, &c2);
    equation->a = a1 - a2;
    equation->b = b1 - b2;
    equation->c = c1 - c2;

    free(left);
    free(right);

    return 1;
}

static int parse(struct Parser *parser, struct QuadraticEquation *equation)
{
    return find_full_coeffs(parser->s, equation);
}

struct Parser init_parser(char *s)
{
    struct Parser parser = {s, 0, &parse};
    parser.is_correct_format = check_format_and_delete_whitespaces(s);
    return parser;
}
