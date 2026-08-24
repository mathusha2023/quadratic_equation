#include "cmd_args.h"
#include "config.h"

void get_args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (!strcmp(arg, "--test") || !strcmp(arg, "-t"))
            ARGS.test = 1;
        if (!strcmp(arg, "--disable-colors"))
            ARGS.colors = 0;
    }
}
