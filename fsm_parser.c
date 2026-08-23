#include "fsm_parser.h"
#include <stdio.h>
#include <ctype.h>
#include "my_assert.h"
#include "config.h"

static int set_eq_state(struct FSMParser *parser)
{
    if (parser->k == -1)
        return 0;
    parser->k = -1;
    parser->state = EQ;
    return 1;
}

static int process_start_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = INTEGER_PART;
    }
    else if (c == '-')
    {
        parser->state = SUB;
    }
    else if ((char)tolower(c) == 'x')
    {
        parser->state = VARIABLE;
    }
    else
        return 0;
    return 1;
}

static int process_integer_part_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = INTEGER_PART;
    }
    else if (c == '.')
    {
        parser->state = FRACTION_PART;
    }
    else if (isspace(c))
    {
        parser->state = SPACE_AFTER_NUM;
    }
    else if (c == '+')
    {
        parser->state = ADD;
    }
    else if (c == '-')
    {
        parser->state = SUB;
    }
    else if (c == '=')
    {
        return set_eq_state(parser);
    }
    else if (c == 'x')
    {
        parser->state = VARIABLE;
    }
    else
    {
        return 0;
    }
    return 1;
}

static int process_fraction_part_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = FRACTION_PART;
    }
    else if (isspace(c))
    {
        parser->state = SPACE_AFTER_NUM;
    }
    else if (c == '+')
    {
        parser->state = ADD;
    }
    else if (c == '-')
    {
        parser->state = SUB;
    }
    else if (c == '=')
    {
        return set_eq_state(parser);
    }
    else if (c == 'x')
    {
        parser->state = VARIABLE;
    }
    else
    {
        return 0;
    }
    return 1;
}

static int process_variable_state(struct FSMParser *parser, char c)
{
    if (c == '^')
    {
        parser->state = POW;
    }
    else if (c == '+')
    {
        parser->state = ADD;
    }
    else if (c == '-')
    {
        parser->state = SUB;
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

static int process_add_sub_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = INTEGER_PART;
    }
    else if (c == 'x')
    {
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

static int process_eq_state(struct FSMParser *parser, char c)
{
    if (isdigit(c))
    {
        parser->state = INTEGER_PART;
    }
    else if (c == 'x')
    {
        parser->state = VARIABLE;
    }
    else if (c == '-')
    {
        parser->state = SUB;
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

static int process_space_after_num_state(struct FSMParser *parser, char c)
{
    if (c == '+')
    {
        parser->state = ADD;
    }
    else if (c == '-')
    {
        parser->state = SUB;
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

static int process_pow_state(struct FSMParser *parser, char c)
{
    if (isdigit(c) && c - '0' <= MAX_POW)
    {
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

static int process_pow_num_state(struct FSMParser *parser, char c)
{
    if (isspace(c))
    {
        parser->state = SPACE_AFTER_NUM;
        return 1;
    }
    return 0;
}

/* возвращает указатель на первый некорректный символ
или NULL в случае успешного парсинга */
static char *parse(struct FSMParser *parser)
{
    char c = 0;
    char *pc = NULL;
    int i = 0;

    for (i = 0; (c = parser->s[i]); i++)
    {
        pc = &parser->s[i];

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
        default:
            return pc;
        }
    }

    // если k = -1, то равно было встречено ровно 1 раз
    return (parser->k == -1 && parser->state != EQ) ? NULL : &parser->s[i];
}

struct FSMParser init_fsmparser(char *s, struct QuadraticEquation *equation)
{
    my_assert(s);

    struct FSMParser parser =
        {.s = s,
         .state = START,
         .equation = equation,
         .k = 1,
         .parse = &parse};
    return parser;
}
