#include <stdio.h>
#include "cli.h"
#include "core/format_handler.h"
#include "core/section.h"


int main(int argc, char **argv)
{
    // command line

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

    // format 

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

    printf("format: %s\n", format_handler->format_name);
    
    // section table

    SectionTable section_table = {0};
    section_table.items = malloc(16 * sizeof(SectionInfo));

    size_t sections_count = format_handler->build_section_table(fp, &section_table);
    if (!sections_count) {
        fprintf(stderr, NO_SECTION_FOUND_ERROR);
        return 1;
    }

    printf("sections found (%zu):\n", sections_count);
    for (size_t i = 0; i < sections_count; ++i) {
        printf("%zu: %s\n", i+1, section_table.items[i].name);
    }

    fclose(fp);
    return 0;
}

