#include "solve_equation.h"

#ifndef FSM_PARSER_H
#define FSM_PARSER_H

enum FSMStates
{
    START,
    INTEGER_PART,
    FRACTION_PART,
    VARIABLE,
    ADD,
    SUB,
    EQ,
    SPACE_AFTER_NUM,
    POW,
    POW_NUM,
    SPACE_AFTER_POW,
    SPACE_AFTER_VARIABLE
};

struct FSMParser
{
    char *s;
    enum FSMStates state;
    struct QuadraticEquation *equation;

    // коэффициент для умножения коэффициентов (1 до равно и -1 после равно)
    int k;

    int curr_index, num_start_index;
    int last_sign;
    double last_coeff;

    /* возвращает указатель на первый некорректный символ
    или NULL в случае успешного парсинга */
    char *(*parse)(struct FSMParser *parser);
};

struct FSMParser init_fsmparser(char *s, struct QuadraticEquation *equation);
void print_fsmparser(struct FSMParser *parser);
#endif // FSM_PARSER_H