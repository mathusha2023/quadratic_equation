#ifndef CONFIG_H
#define CONFIG_H

// colors block
#define USE_COLORS // comment this line to disable colors
#define RESET_C "\x1b[0m"

#ifdef USE_COLORS // if defined, colors should be valid

#define RED_C "\x1b[31m"
#define GREEN_C "\x1b[32m"
#define BLUE_C "\x1b[34m"
#define YELLOW_C "\x1b[33m"

#else // if USE_COLORS isnt defined, use RESET_C

#define RED_C RESET_C
#define GREEN_C RESET_C
#define BLUE_C RESET_C
#define YELLOW_C RESET_C

#endif // USE_COLORS
// colors block end

#define EPSILON 0.0001
#define d_is_equal(a, b) (fabs((a) - (b)) < EPSILON)

#endif // CONFIG_H