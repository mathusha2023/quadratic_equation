#include "fsm_parser.h"

/**
 * @brief Process start state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_start_state(struct FSMParser *parser, char c);

/**
 * @brief Process integer part state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_integer_part_state(struct FSMParser *parser, char c);

/**
 * @brief Process dot state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_dot_state(struct FSMParser *parser, char c);

/**
 * @brief Process fraction part state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_fraction_part_state(struct FSMParser *parser, char c);

/**
 * @brief Process variable state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_variable_state(struct FSMParser *parser, char c);

/**
 * @brief Process add or sub state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_add_sub_state(struct FSMParser *parser, char c);

/**
 * @brief Process space after num state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_space_after_num_state(struct FSMParser *parser, char c);

/**
 * @brief Process eq state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_eq_state(struct FSMParser *parser, char c);

/**
 * @brief Process pow state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_pow_state(struct FSMParser *parser, char c);

/**
 * @brief Process pow num state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_pow_num_state(struct FSMParser *parser, char c);

/**
 * @brief Process space after variable state
 *
 * @param parser
 * @param c
 * @return int 1 if c is correct else 0
 */
int process_space_after_variable_state(struct FSMParser *parser, char c);