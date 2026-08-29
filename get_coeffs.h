#include "solve_equation.h"

/**
 * @brief Print the program logo if exists
 *
 */
void print_logo(void);

/**
 * @brief Print the program greeting
 *
 */
void print_greeting(void);

/**
 * @brief Get the coeffs to equation
 *
 * This function get coeffs from console and put them to equation.
 * Coeffs getting will be in loop - until user enter wrong coeffs the loop will continue
 *
 * @param equation
 */
void get_coeffs_in_loop(struct QuadraticEquation *equation);
