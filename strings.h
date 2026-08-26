#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "my_assert.h"

const char ARROW_S[] = "------> ";
const char GREETING_S[] = "Очень добрый день! Я - новейшая разработка\n"
                          "одного из гениальнейших умов мира, и я\n"
                          "умею решать абсолютно все типы квадратных\n"
                          "уравнений. Пожалуйста, введите ваше\n"
                          "задание, и я обязательно решу его, бип\n";
const char THINKING_S[] = "Какое интересное задание! Сейчас подумаю, бип...\n";
const char SOLVED_S[] = "Извините за задержку, я решил! Ответы оформил ниже, бип\n";
const char ERROR_S[] = "Упс, кажется, вы ввели некорректное квадратное\n"
                       "уравнение. Бубс показал, где именно ошибка.\n"
                       "Попробуйте ввести задание еще раз, бип\n";

static void print_phrase(const char *s)
{
    my_assert(s);

    printf("%s%s", YELLOW_C, ARROW_S);
    char c = 0;
    const double sleep_time = 0.02; // seconds

    for (int i = 0; (c = s[i]); i++)
    {
        putchar(c);
        if (ARGS.output_delay)
        {
            fflush(stdout);
            usleep((useconds_t)(1e6 * sleep_time)); // in microseconds
        }
    }
    printf("%s", RESET_C);
}

#endif // STRINGS_H
