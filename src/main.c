#include <stdio.h>
#include "cli.h"
#include "core/format_handler.h"
#include "core/section.h"

#include "format/png/png_chunks.h" // TMP


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

    size_t sections_count = format_handler->build_section_table(fp, &section_table);
    if (!sections_count) {
        fprintf(stderr, NO_SECTION_FOUND_ERROR);
        return 1;
    }

    printf("sections found (%zu):\n", sections_count);
    for (size_t i = 0; i < sections_count; ++i) {
        printf("%zu: %s\n", i+1, section_table.items[i].name);
    }


    // TMP: png_parse_IHDR
    fseek(fp, 16, SEEK_SET);
    char ihdr_buffer[50];
    fread(ihdr_buffer, 1, 16, fp);
    SectionResult r = png_parse_IHDR(ihdr_buffer, sizeof(ihdr_buffer), NULL);
    printf("(%s) %s: %d\n", r.section_name, r.items[0].label, r.items[0].as_int); // width
    printf("(%s) %s: %d\n", r.section_name, r.items[1].label, r.items[1].as_int); // height
    printf("(%s) %s: %d\n", r.section_name, r.items[2].label, r.items[2].as_int); // bit depth
    printf("(%s) %s: %d -> %s\n", r.section_name, r.items[3].label, r.items[3].as_enum.raw, r.items[3].as_enum.resolved_label); // color type
    printf("(%s) %s: %d -> %s\n", r.section_name, r.items[4].label, r.items[4].as_enum.raw, r.items[4].as_enum.resolved_label); // compression method
    printf("(%s) %s: %d -> %s\n", r.section_name, r.items[5].label, r.items[5].as_enum.raw, r.items[5].as_enum.resolved_label); // filter method
    printf("(%s) %s: %d -> %s\n", r.section_name, r.items[6].label, r.items[6].as_enum.raw, r.items[6].as_enum.resolved_label); // interlace method


    fclose(fp);
    return 0;
}

