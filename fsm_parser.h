#include "solve_equation.h"

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
    POW_NUM
};

struct FSMParser
{
    char *s;
    enum FSMStates state;
    struct QuadraticEquation *equation;

    // коэффициент для умножения коэффициентов (1 до равно и -1 после равно)
    int k;

    /* возвращает указатель на первый некорректный символ
    или NULL в случае успешного парсинга */
    char *(*parse)(struct FSMParser *parser);
};

struct FSMParser init_fsmparser(char *s, struct QuadraticEquation *equation);
