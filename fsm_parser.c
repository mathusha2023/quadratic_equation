#include "fsm_parser.h"
#include <stdio.h>
#include <ctype.h>
#include "my_assert.h"
#include "fsm_parser_processes.h"

static int check_correct_end_parsing(struct FSMParser *parser)
{
    my_assert(parser);

    // если k = -1, то равно было встречено ровно 1 раз
    return parser->k == -1 && parser->state != EQ &&
           parser->state != ADD && parser->state != SUB &&
           parser->state != DOT && parser->state != POW;
}

/* возвращает указатель на первый некорректный символ
или NULL в случае успешного парсинга */
static char *parse(struct FSMParser *parser)
{
    my_assert(parser);

    char c = 0;
    char *pc = NULL;

    for (parser->curr_index = 0; parser->s[parser->curr_index]; parser->curr_index++)
    {
        c = (char)tolower(parser->s[parser->curr_index]);
        pc = &parser->s[parser->curr_index];

        switch (parser->state)
        {
        case START:
            if (!process_start_state(parser, c))
                return pc;
            break;
        case INTEGER_PART:
            if (!process_integer_part_state(parser, c))
                return pc;
            break;
        case DOT:
            if (!process_dot_state(parser, c))
                return pc;
            break;
        case FRACTION_PART:
            if (!process_fraction_part_state(parser, c))
                return pc;
            break;
        case VARIABLE:
            if (!process_variable_state(parser, c))
                return pc;
            break;
        case ADD:
            if (!process_add_sub_state(parser, c))
                return pc;
            break;
        case SUB:
            if (!process_add_sub_state(parser, c))
                return pc;
            break;
        case EQ:
            if (!process_eq_state(parser, c))
                return pc;
            break;
        case SPACE_AFTER_NUM:
            if (!process_space_after_num_state(parser, c))
                return pc;
            break;
        case POW:
            if (!process_pow_state(parser, c))
                return pc;
            break;
        case POW_NUM:
            if (!process_pow_num_state(parser, c))
                return pc;
            break;
        case SPACE_AFTER_VARIABLE:
            if (!process_space_after_variable_state(parser, c))
                return pc;
            break;
        default:
            return pc;
        }
    }
    return check_correct_end_parsing(parser) ? NULL : &parser->s[parser->curr_index];
}

static const char *get_str_state(enum FSMStates state)
{
    static const char *states_str[] = {"START",
                                       "INTEGER_PART",
                                       "DOT",
                                       "FRACTION_PART",
                                       "VARIABLE",
                                       "ADD",
                                       "SUB",
                                       "EQ",
                                       "SPACE_AFTER_NUM",
                                       "POW",
                                       "POW_NUM",
                                       "SPACE_AFTER_VARIABLE"};
    return states_str[state];
}

void print_fsmparser(struct FSMParser *parser)
{
    my_assert(parser);

    printf("Parser data:\n"
           ".s = %s\n"
           ".state = %s\n"
           ".k = %d\n"
           ".curr_index = %d\n"
           ".num_start_index = %d\n"
           ".last_sign = %d\n"
           ".last_coeff = %lg\n",
           parser->s,
           get_str_state(parser->state),
           parser->k,
           parser->curr_index,
           parser->num_start_index,
           parser->last_sign,
           parser->last_coeff);
    print_equation(parser->equation);
}

struct FSMParser init_fsmparser(char *s, struct QuadraticEquation *equation)
{
    my_assert(s);
    my_assert(equation);

    equation->a = 0;
    equation->b = 0;
    equation->c = 0;

    struct FSMParser parser =
        {.s = s,
         .state = START,
         .equation = equation,
         .k = 1,
         .curr_index = 0,
         .num_start_index = 0,
         .last_sign = 1,
         .last_coeff = 0.,
         .parse = &parse};
    return parser;
}
