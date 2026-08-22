#include "solve_equation.h"

struct Parser
{
    char *s;
    int (*check_format)(struct Parser *parser);
    int (*parse)(struct Parser *parser, struct QuadraticEquation *equation);
};

struct Parser init_parser(char *s);
