#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define my_assert(condition)                               \
    {                                                      \
        if (!(condition))                                  \
        {                                                  \
            fprintf(stderr, "\x1b[31m"                     \
                            "My asseration error: %s:%d\n" \
                            "\x1b[0m",                     \
                    __FILE__, __LINE__);                   \
            exit(1);                                       \
        }                                                  \
    }

#endif // MY_ASSERT_H