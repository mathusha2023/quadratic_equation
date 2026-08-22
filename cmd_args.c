#include "cmd_args.h"

struct CmdArgs get_args(int argc, char *argv[])
{
    struct CmdArgs args = {0, 1};
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (!strcmp(arg, "--test") || !strcmp(arg, "-t"))
            args.test = 1;
        if (!strcmp(arg, "--disable-colors"))
            args.colors = 0;
    }
    return args;
}