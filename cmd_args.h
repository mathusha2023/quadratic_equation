#ifndef CMD_ARGS_H
#define CMD_ARGS_H

#include <string.h>

/**
 * @brief Struct of allowed cmd args
 *
 * All command-line arguments passed at startup are preserved here
 * All arguments can have 2 values: 0 and 1
 *
 */
struct CmdArgs
{
    int test;
    int colors;
    int output_delay;
    int speech;
    int ascii_arts;
    int ascii_graph;
    int graph_window;
};

/**
 * @brief Get the args object from argc and argv
 *
 * This function writes args in global CmdArgs object
 *
 * @param argc
 * @param argv
 */
void get_args(int argc, char *argv[]);

#endif // CMD_ARGS_H