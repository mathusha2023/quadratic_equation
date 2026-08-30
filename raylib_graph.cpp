#include "raylib_graph.h"
#include "raylib.h"
#include "graph.h"
#include "solve_equation.h"
#include "my_assert.h"
#include "config.h"

static void draw_axises()
{
    struct Color axis_color = BLACK;
    struct Vector2 center = {GRAPH_WINDOW_WIDTH / 2, GRAPH_WINDOW_HIGHT / 2};

    // Draw x-axis
    DrawLine(GRAPH_PADDING, (int)center.y, GRAPH_WINDOW_WIDTH - GRAPH_PADDING, (int)center.y, axis_color);
    DrawLine(GRAPH_WINDOW_WIDTH - GRAPH_PADDING - AXIS_ARROW_LENGTH,
             (int)center.y - AXIS_ARROW_LENGTH,
             GRAPH_WINDOW_WIDTH - GRAPH_PADDING,
             (int)center.y,
             axis_color);
    DrawLine(GRAPH_WINDOW_WIDTH - GRAPH_PADDING,
             (int)center.y,
             GRAPH_WINDOW_WIDTH - GRAPH_PADDING - AXIS_ARROW_LENGTH,
             (int)center.y + AXIS_ARROW_LENGTH,
             axis_color);
    DrawText("x", GRAPH_WINDOW_WIDTH - GRAPH_PADDING, (int)center.y, FONT_SIZE, axis_color);

    // Draw y-axis
    DrawLine((int)center.x, GRAPH_PADDING, (int)center.y, GRAPH_WINDOW_HIGHT - GRAPH_PADDING, axis_color);
    DrawLine((int)center.x - AXIS_ARROW_LENGTH,
             GRAPH_PADDING + AXIS_ARROW_LENGTH,
             (int)center.x,
             GRAPH_PADDING,
             axis_color);
    DrawLine((int)center.x,
             GRAPH_PADDING,
             (int)center.x + AXIS_ARROW_LENGTH,
             GRAPH_PADDING + AXIS_ARROW_LENGTH,
             axis_color);
    DrawText("y", (int)center.x + AXIS_ARROW_LENGTH, GRAPH_PADDING, FONT_SIZE, axis_color);
}

static void draw_horizontal_line(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(d_is_equal(equation->a, 0));
    my_assert(d_is_equal(equation->b, 0));
}

static void draw_line(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(d_is_equal(equation->a, 0));

    if (d_is_equal(equation->b, 0))
        return draw_horizontal_line(equation);
}

static void draw_parabola(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(!d_is_equal(equation->a, 0));
}

static void draw_graph(struct QuadraticEquation *equation)
{
    my_assert(equation);

    if (d_is_equal(equation->a, 0))
        return draw_line(equation);
    return draw_parabola(equation);
}

void show_graph_window(struct QuadraticEquation *equation)
{
    my_assert(equation);

    const static int fps = 30;
    InitWindow(GRAPH_WINDOW_WIDTH, GRAPH_WINDOW_HIGHT, GRAPH_WINDOW_NAME);

    SetTargetFPS(fps);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);
        draw_axises();
        draw_graph(equation);

        EndDrawing();
    }

    CloseWindow();
}