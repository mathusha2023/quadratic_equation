#ifndef CONFIG_H
#define CONFIG_H

#include <math.h>
#include "cmd_args.h"

// colors block
#define RESET_C "\x1b[0m"

#define use_color(color) (ARGS.colors ? color : RESET_C)

#define RED_C use_color("\x1b[31m")
#define GREEN_C use_color("\x1b[32m")
#define BLUE_C use_color("\x1b[34m")
#define YELLOW_C use_color("\x1b[33m")
// colors block end

const size_t BUFFERSIZE = 100;
const double EPSILON = 1e-6;
const int MAX_POW = 2;

// глобальная для всей программы переменная,
// которая будет содержать аргументы командной строки после запуска программы
extern struct CmdArgs ARGS;

#define d_is_equal(a, b) (fabs((a) - (b)) < EPSILON)

#endif // CONFIG_H