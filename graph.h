const int X_AXIS_LEN = 80;
const int Y_AXIS_LEN = 40;
const double MIN_SCALE = 1e-6;

struct Point
{
    double x, y;
};

void draw_quadratic_equation_graph(struct QuadraticEquation *equation);
