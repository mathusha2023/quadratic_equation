#include "cmd_args.h"
#include "config.h"

void get_args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (!strcmp(arg, TEST_ARG))
            ARGS.test = 1;
        else if (!strcmp(arg, DISABLE_COLORS_ARG))
            ARGS.colors = 0;
        else if (!strcmp(arg, DISABLE_OUTPUT_DELAY_ARG))
            ARGS.output_delay = 0;
        else if (!strcmp(arg, DISABLE_SPEECH_ARG))
            ARGS.speech = 0;
        else if (!strcmp(arg, DISABLE_GRAPH_ARG))
            ARGS.graph = 0;
        else if (!strcmp(arg, DISABLE_ASCII_ARTS))
            ARGS.ascii_arts = 0;
        else if (!strcmp(arg, DISABLE_ALL))
        {
            ARGS.colors = 0;
            ARGS.output_delay = 0;
            ARGS.speech = 0;
            ARGS.graph = 0;
            ARGS.ascii_arts = 0;
        }
    }
}
