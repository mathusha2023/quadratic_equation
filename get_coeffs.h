#include "solve_equation.h"

void get_coeffs_in_loop(struct QuadraticEquation *equation, int (*pfunction)(struct QuadraticEquation *equation));
int get_coeffs(struct QuadraticEquation *equation);
int parse_coeffs_from_equation(struct QuadraticEquation *equation);