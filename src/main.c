#include <stdio.h>
#include "cli.h"
#include "core/format_handler.h"


int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, USAGE);
        return 1;
    }

    Options cli_options;
    if (!parse_args(argc, argv, &cli_options)) {
        fprintf(stderr, INVALID_ARGUMENT_ERROR);
        return 1;
    }

    if (cli_options.mode == HELP) {
        fprintf(stderr, USAGE);
        return 1;
    }

    // printf("mode: %d\n", cli_options.mode);
    // printf("path: %s\n", cli_options.path);
    // printf("section name: %s\n", cli_options.section_name);

    FILE *fp = fopen(cli_options.path, "r");
    if (!fp) {
        fprintf(stderr, FILE_ACCESS_ERROR); 
        return 1;
    }

    const ImageFormatHandler *format_handler = detect_format(fp);

    if (!format_handler) {
        fprintf(stderr, UNRECOGNIZED_FORMAT_ERROR);
        return 1;
    }

    // printf("format: %s\n", format_handler->format_name);

    return 0;
}

