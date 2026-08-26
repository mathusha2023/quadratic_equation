#include "cmd_args.h"
#include "config.h"

void get_args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (!strcmp(arg, TEST_ARG))
            ARGS.test = 1;
        if (!strcmp(arg, DISABLE_COLORS_ARG))
            ARGS.colors = 0;
        if (!strcmp(arg, DISABLE_OUTPUT_DELAY_ARG))
            ARGS.output_delay = 0;
    }
}
