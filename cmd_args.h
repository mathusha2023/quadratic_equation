#ifndef CMD_ARGS_H
#define CMD_ARGS_H

#include <string.h>

struct CmdArgs
{
    int test;
    int colors;
    int output_delay;
};

void get_args(int argc, char *argv[]);

#endif // CMD_ARGS_H