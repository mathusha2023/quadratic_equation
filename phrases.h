#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "my_assert.h"

// Phrases for BAA GPT
const char ARROW_S[] = "------> ";
const char GREETING_S[] = "Очень добрый день! Я - новейшая разработка\n"
                          "одного из гениальнейших умов мира, и я\n"
                          "умею решать абсолютно все типы квадратных\n"
                          "уравнений. Пожалуйста, введите ваше\n"
                          "задание, и я обязательно решу его, бип\n";
const char THINKING_S[] = "Какое интересное задание! Сейчас подумаю, бип...\n";
const char SOLVED_S[] = "Извините за задержку, я решила! Ответы оформила ниже, бип\n";
const char ERROR_S[] = "Упс, кажется, вы ввели некорректное квадратное\n"
                       "уравнение. Бубс показал, где именно ошибка.\n"
                       "Попробуйте ввести задание еще раз, бип\n";
// End phrases

/**
 * @brief Print received phrase
 *
 * @param s
 */
void print_phrase(const char *s);

/**
 * @brief Say received phrase
 *
 * @note This function works only on macos and uses say command
 *
 * @param s
 */
void say(const char *s);

/**
 * @brief Combine print_phrase() and say() functions
 *
 * @param s
 */
void print_and_say_phrase(const char *s);

#endif // STRINGS_H
