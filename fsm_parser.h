#ifndef FSM_PARSER_H
#define FSM_PARSER_H

#include "solve_equation.h"

/**
 * @brief State machine states
 *
 */
enum FSMStates
{
    START,
    INTEGER_PART,
    DOT,
    FRACTION_PART,
    VARIABLE,
    ADD,
    SUB,
    EQ,
    SPACE_AFTER_NUM,
    POW,
    POW_NUM,
    SPACE_AFTER_VARIABLE
};

/**
 * @brief Parser with finite state machine
 *
 */
struct FSMParser
{
    char *s;                            ///< input string
    enum FSMStates state;               ///< current state
    struct QuadraticEquation *equation; ///< quadratic equation to write coefficients

    int k; ///< coefficient to multiply parsed numbers (1 before =, -1 after =)

    int curr_index;      ///< current index in string
    int num_start_index; ///< start index of number for parsing
    int last_sign;       ///< sign of last parsed number
    double last_coeff;   ///< last parsed number

    /**
     * @brief Parse string to quadratic equation
     *
     * @param parser
     * @return char* pointer to first incorrect symbol if there is else NULL
     *
     */
    char *(*parse)(struct FSMParser *parser);
};

/**
 * @brief Initialize finite state machine parser
 *
 * @param s string to parse
 * @param equation
 * @return struct FSMParser
 */
struct FSMParser init_fsmparser(char *s, struct QuadraticEquation *equation);

/**
 * @brief Print finite state machine parser
 *
 * @param parser
 */
void print_fsmparser(struct FSMParser *parser);

#endif // FSM_PARSER_H