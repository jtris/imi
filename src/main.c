#include <stdio.h>
#include "cli.h"


int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, USAGE);
        return 1;
    }

    Options cli_options;
    if (!parse_args(argc, argv, &cli_options)) {
        fprintf(stderr, INVALID_ARGUMENTS "\n" USAGE);
        return 1;
    }

    return 0;
}

