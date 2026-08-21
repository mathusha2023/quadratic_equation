#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#define my_assert(condition) _myassert(condition, __FILE__, __LINE__)

void _myassert(int condition, const char *file, int line);

#endif // MY_ASSERT_H