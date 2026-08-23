#include "fsm_parser_processes.h"
#include "fsm_parser.h"
#include <ctype.h>
#include <stdlib.h>
#include "config.h"

static int set_eq_state(struct FSMParser *parser)
{
    if (parser->k == -1)
        return 0;
    parser->k = -1;
    parser->last_coeff = 1;
    parser->last_sign = 1;
    parser->state = EQ;
    return 1;
}

static int set_add_sub_state(enum FSMStates state, struct FSMParser *parser)
{
    if (state == ADD || state == SUB)
    {
        parser->last_sign = (state == ADD ? 1 : -1);
        parser->state = state;
        return 1;
    }
    return 0;
}

static void parse_coeff(struct FSMParser *parser)
{
    parser->last_coeff = strtod(parser->s + parser->num_start_index, NULL);
}

static void update_coeff(struct FSMParser *parser, double *coeff)
{
    *coeff += parser->k * parser->last_sign * parser->last_coeff;
}

static void parse_and_update_coeff(struct FSMParser *parser, double *coeff)
{
    parse_coeff(parser);
    update_coeff(parser, coeff);
}

int process_start_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = INTEGER_PART;
    }
    else if (c == '-')
    {
        return set_add_sub_state(SUB, parser);
    }
    else if (c == 'x')
    {
        parser->state = VARIABLE;
        parser->last_coeff = 1;
    }
    else
        return 0;
    return 1;
}

int process_integer_part_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        ;
    }
    else if (c == '.')
    {
        parser->state = FRACTION_PART;
    }
    else if (isspace(c))
    {
        parse_and_update_coeff(parser, &parser->equation->c);
        parser->state = SPACE_AFTER_NUM;
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
        parser->state = VARIABLE;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_fraction_part_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        ;
    }
    else if (isspace(c))
    {
        parse_and_update_coeff(parser, &parser->equation->c);
        parser->state = SPACE_AFTER_NUM;
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
        parser->state = VARIABLE;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_variable_state(struct FSMParser *parser, char c)
{
    if (c == '^')
    {
        parser->state = POW;
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
        parser->state = SPACE_AFTER_VARIABLE;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_add_sub_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->num_start_index = parser->curr_index;
        parser->state = INTEGER_PART;
    }
    else if (c == 'x')
    {
        parser->last_coeff = 1;
        parser->state = VARIABLE;
    }
    else if (isspace(c))
    {
        ;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_eq_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = INTEGER_PART;
        parser->num_start_index = parser->curr_index;
    }
    else if (c == 'x')
    {
        parser->last_coeff = 1;
        parser->state = VARIABLE;
    }
    else if (c == '-')
    {
        return set_add_sub_state(SUB, parser);
    }
    else if (isspace(c))
    {
        ;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_space_after_num_state(struct FSMParser *parser, char c)
{
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
    {
        ;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_pow_state(struct FSMParser *parser, char c)
{
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
        parser->state = POW_NUM;
    }
    else if (isspace(c))
    {
        ;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_pow_num_state(struct FSMParser *parser, char c)
{
    if (isspace(c))
    {
        parser->state = SPACE_AFTER_POW;
        return 1;
    }
    return 0;
}

int process_space_after_pow_state(struct FSMParser *parser, char c)
{
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
    {
        ;
    }
    else
    {
        return 0;
    }
    return 1;
}

int process_space_after_variable_state(struct FSMParser *parser, char c)
{
    if (c == '+')
    {
        return set_add_sub_state(ADD, parser);
    }
    else if (c == '-')
    {
        return set_add_sub_state(SUB, parser);
    }
    else if (c == '^')
    {
        parser->state = POW;
    }
    else if (c == '=')
    {
        return set_eq_state(parser);
    }
    else if (isspace(c))
    {
        ;
    }
    else
    {
        return 0;
    }
    return 1;
}