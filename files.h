#include <stdio.h>

/**
 * @brief Copy one file to other
 *
 * This function copy all data from ifp to ofp
 *
 * @param ifp File copy from
 * @param ofp File copy to
 */
void filecopy(FILE *ifp, FILE *ofp);

/**
 * @brief Print file to stdout
 *
 * This function print input file to console using transferred color
 *
 * @param file_path
 * @param color sequence of characters that set sth color
 * @return int 1 if successfully printed else 0
 */
int print_file(const char *file_path, const char *color);

/**
 * @brief Print file string number [n]
 *
 * @note Numeration starts from 0
 * @param path
 * @param n string's number, the first string have number 0
 * @param new_line can be {0, 1} - 1 if should print line break else 0
 * @return int 1 if successfulle printed else 0
 */
int print_n_file_string(const char *path, int n, int new_line);
