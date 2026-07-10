#include <stdio.h>
#include "cli.h"


int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        PRINT_USAGE(stderr);
        return 1;
    }

    Options cli_options;
    if (!parse_args(argc, argv, &cli_options)) {
        PRINT_INVALID_ARGUMENT_ERROR(stderr);
        return 1;
    }

    if (cli_options.mode == HELP) {
        PRINT_USAGE(stderr);
        return 1;
    }

    printf("mode: %d\n", cli_options.mode);
    printf("path: %s\n", cli_options.path);
    printf("chunk name: %s\n", cli_options.chunk_name);

    return 0;
}

