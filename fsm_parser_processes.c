#include "fsm_parser_processes.h"
#include "fsm_parser.h"
#include <ctype.h>
#include <stdlib.h>
#include "config.h"
#include "my_assert.h"

/**
 * @brief Set the state object to parser
 *
 * @param parser
 * @param state
 */
static void set_state(struct FSMParser *parser, enum FSMStates state)
{
    my_assert(parser);

    parser->state = state;
}

/**
 * @brief Set the eq state object to parser
 *
 * Set the eq state to parser, including changes in coeffs,
 * and checks whether this was done previously
 *
 * @param parser
 * @return int 1 if success else 0
 */
static int set_eq_state(struct FSMParser *parser)
{
    my_assert(parser);

    if (parser->k == -1)
        return 0;
    parser->k = -1;
    parser->last_coeff = 1;
    parser->last_sign = 1;
    set_state(parser, EQ);
    return 1;
}

/**
 * @brief Set the add or sub state object to parser
 *
 * Set add or sub parser state and change its last sign
 *
 * @param state
 * @param parser
 * @return int 1 if success else 0
 */
static int set_add_sub_state(enum FSMStates state, struct FSMParser *parser)
{
    my_assert(parser);

    if (state == ADD || state == SUB)
    {
        parser->last_sign = (state == ADD ? 1 : -1);
        set_state(parser, state);
        return 1;
    }
    return 0;
}

/**
 * @brief Save last coeff from string
 *
 * Parse last coeff from parser string and save it
 *
 * @param parser
 */
static void parse_coeff(struct FSMParser *parser)
{
    my_assert(parser);

    parser->last_coeff = strtod(parser->s + parser->num_start_index, NULL);
}

/**
 * @brief Add last saved coeff to transfered coeff (a, b or c)
 *
 * @param parser
 * @param coeff
 */
static void update_coeff(struct FSMParser *parser, double *coeff)
{
    my_assert(parser);
    my_assert(coeff);

    *coeff += parser->k * parser->last_sign * parser->last_coeff;
}

/**
 * @brief Combination of parse_coeff() and update_coeff()
 *
 * @param parser
 * @param coeff
 */
static void parse_and_update_coeff(struct FSMParser *parser, double *coeff)
{
    parse_coeff(parser);
    update_coeff(parser, coeff);
}

// processing functions

int process_start_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (isdigit(c))
    {
        set_state(parser, INTEGER_PART);
        parser->num_start_index = parser->curr_index;
    }
    else if (c == '-')
    {
        return set_add_sub_state(SUB, parser);
    }
    else if (c == 'x')
    {
        set_state(parser, VARIABLE);
        parser->last_coeff = 1;
    }
    else
        return 0;
    return 1;
}

int process_integer_part_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (process_fraction_part_state(parser, c))
        return 1;

    else if (c == '.')
    {
        set_state(parser, DOT);
        return 1;
    }
    return 0;
}

int process_dot_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (isdigit(c))
    {
        set_state(parser, FRACTION_PART);
        return 1;
    }
    return 0;
}

int process_fraction_part_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (isdigit(c))
    {
        ;
    }
    else if (isspace(c))
    {
        parse_and_update_coeff(parser, &parser->equation->c);
        set_state(parser, SPACE_AFTER_NUM);
    }
    else if (c == '+')
    {
        parse_and_update_coeff(parser, &parser->equation->c);
        return set_add_sub_state(ADD, parser);
    }
    else if (c == '-')
    {
        parse_and_update_coeff(parser, &parser->equation->c);
        return set_add_sub_state(SUB, parser);
    }
    else if (c == '=')
    {
        parse_and_update_coeff(parser, &parser->equation->c);
        return set_eq_state(parser);
    }
    else if (c == 'x')
    {
        parse_coeff(parser);
        set_state(parser, VARIABLE);
    }
    else
        return 0;
    return 1;
}

int process_variable_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (c == '^')
    {
        set_state(parser, POW);
    }
    else if (c == '+')
    {
        update_coeff(parser, &parser->equation->b);
        return set_add_sub_state(ADD, parser);
    }
    else if (c == '-')
    {
        update_coeff(parser, &parser->equation->b);
        return set_add_sub_state(SUB, parser);
    }
    else if (c == '=')
    {
        update_coeff(parser, &parser->equation->b);
        return set_eq_state(parser);
    }
    else if (isspace(c))
    {
        update_coeff(parser, &parser->equation->b);
        set_state(parser, SPACE_AFTER_VARIABLE);
    }
    else
        return 0;
    return 1;
}

int process_add_sub_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (isdigit(c))
    {
        parser->num_start_index = parser->curr_index;
        set_state(parser, INTEGER_PART);
    }
    else if (c == 'x')
    {
        parser->last_coeff = 1;
        set_state(parser, VARIABLE);
    }
    else if (isspace(c))
        ;
    else
        return 0;
    return 1;
}

int process_eq_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (process_start_state(parser, c) || isspace(c))
        return 1;
    return 0;
}

int process_space_after_num_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (c == '+')
    {
        return set_add_sub_state(ADD, parser);
    }
    else if (c == '-')
    {
        return set_add_sub_state(SUB, parser);
    }
    else if (c == '=')
    {
        return set_eq_state(parser);
    }
    else if (isspace(c))
        ;
    else
        return 0;
    return 1;
}

int process_pow_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    int pow = (int)(c - '0');
    if (isdigit(c) && pow <= MAX_POW)
    {
        switch (pow)
        {
        case 0:
            update_coeff(parser, &parser->equation->c);
            break;
        case 1:
            update_coeff(parser, &parser->equation->b);
            break;
        case 2:
            update_coeff(parser, &parser->equation->a);
            break;
        default:
            return 0;
        }
        set_state(parser, POW_NUM);
    }
    else if (isspace(c))
        ;
    else
        return 0;
    return 1;
}

int process_pow_num_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (isspace(c))
    {
        set_state(parser, SPACE_AFTER_NUM);
        return 1;
    }
    else if (c == '+')
    {
        return set_add_sub_state(ADD, parser);
    }
    else if (c == '-')
    {
        return set_add_sub_state(SUB, parser);
    }
    else if (c == '=')
    {
        return set_eq_state(parser);
    }
    return 0;
}

int process_space_after_variable_state(struct FSMParser *parser, char c)
{
    my_assert(parser);

    if (process_space_after_num_state(parser, c))
        return 1;
    else if (c == '^')
    {
        set_state(parser, POW);
        return 1;
    }
    return 0;
}
