#ifndef CONFIG_H
#define CONFIG_H

#include <math.h>
#include "cmd_args.h"

// colors block
#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"
#define BLUE_COLOR "\x1b[34m"
#define YELLOW_COLOR "\x1b[33m"
#define CYAN_COLOR "\x1b[36m"
#define RESET_COLOR "\x1b[0m"

// Macros that check if ARGS.colors = 1 and returns color or no color
#define use_color(color) (ARGS.colors ? color : RESET_COLOR)

// Colors that paint console only if ARGS.colors = 1
#define RED_C use_color(RED_COLOR)
#define GREEN_C use_color(GREEN_COLOR)
#define BLUE_C use_color(BLUE_COLOR)
#define YELLOW_C use_color(YELLOW_COLOR)
#define CYAN_C use_color(CYAN_COLOR)
#define RESET_C use_color(RESET_COLOR)

// colors block end

// cmd args block
#define TEST_ARG "--test"
#define DISABLE_COLORS_ARG "--disable-colors"
#define DISABLE_OUTPUT_DELAY_ARG "--disable-output-delay"
#define DISABLE_SPEECH_ARG "--disable-speech"
#define DISABLE_GRAPH_ARG "--disable-graph"
#define DISABLE_ASCII_ARTS "--disable-ascii-arts"
#define DISABLE_ALL "--disable-all"
// cmd args block end

// file path block
#define START_F "ascii_arts/start.txt"
#define N1_F "ascii_arts/1.txt"
#define N2_F "ascii_arts/2.txt"
#define N3_F "ascii_arts/3.txt"
#define N4_F "ascii_arts/4.txt"
#define N5_F "ascii_arts/5.txt"
#define N6_F "ascii_arts/6.txt"
#define N7_F "ascii_arts/7.txt"
#define N8_F "ascii_arts/8.txt"
#define N9_F "ascii_arts/9.txt"
#define N0_F "ascii_arts/0.txt"
#define DOT_F "ascii_arts/dot.txt"
#define POW_F "ascii_arts/pow.txt"
#define ADD_F "ascii_arts/add.txt"
#define SUB_F "ascii_arts/sub.txt"
#define EQ_F "ascii_arts/eq.txt"
#define X_F "ascii_arts/x.txt"
#define E_F "ascii_arts/e.txt"
// file path block end

// line break block
#define disable_line_break() printf("\033[?7l")
#define enable_line_break() printf("\033[?7h")
// line break block end

const size_t BUFFERSIZE = 100;
const double EPSILON = 1e-6;
const int MAX_POW = 2;

/**
 * @brief Global variable with cmd args
 *
 * This variable saves all running arguments. Its global because all parts of program
 * need it, especially macros use_color(color). This variable ensures correct colors settings.
 * The initialization with default values is in main.c, but get_args() change this with got args
 *
 * @warning This variable is global. Dont change it after using get_args()!!!
 *
 */
extern struct CmdArgs ARGS;

// check if equal two [double]
#define d_is_equal(a, b) (fabs((a) - (b)) < EPSILON)

#endif // CONFIG_H