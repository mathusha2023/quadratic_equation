#include "fsm_parser.h"

int process_start_state(struct FSMParser *parser, char c);
int process_integer_part_state(struct FSMParser *parser, char c);
int process_fraction_part_state(struct FSMParser *parser, char c);
int process_variable_state(struct FSMParser *parser, char c);
int process_add_sub_state(struct FSMParser *parser, char c);
int process_space_after_num_state(struct FSMParser *parser, char c);
int process_eq_state(struct FSMParser *parser, char c);
int process_pow_state(struct FSMParser *parser, char c);
int process_pow_num_state(struct FSMParser *parser, char c);
int process_space_after_pow_state(struct FSMParser *parser, char c);
int process_space_after_variable_state(struct FSMParser *parser, char c);