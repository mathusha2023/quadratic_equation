#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define my_assert(condition)                                                      \
    {                                                                             \
        if (!(condition))                                                         \
        {                                                                         \
            /* красный цвет для печати + его сброс */                             \
            fprintf(stderr, RED_COLOR "My asseration error: %s:%d\n" RESET_COLOR, \
                    __FILE__, __LINE__);                                          \
            exit(1);                                                              \
        }                                                                         \
    }

#endif // MY_ASSERT_H