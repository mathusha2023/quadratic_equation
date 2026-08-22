#include <string.h>

struct CmdArgs
{
    int test;
    int colors;
};

struct CmdArgs get_args(int argc, char *argv[]);