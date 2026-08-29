/**
 * @file
 *
 * @deprecated This parser is deprecated, please use FSMParser
 *
 */
#include "solve_equation.h"

/**
 * @brief Parser struct (old)
 *
 * @deprecated This parser is deprecated, please use FSMParser
 */
struct Parser
{
    char *s;
    const int is_correct_format;
    int (*parse)(struct Parser *parser, struct QuadraticEquation *equation);
};
/**
 * @brief Init deprecated parser
 *
 * @deprecated This parser is deprecated, please use FSMParser
 *
 * @param s
 * @return struct Parser
 */
struct Parser init_parser(char *s);
