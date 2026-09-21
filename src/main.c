#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "core/format_handler.h"
#include "core/section.h"
#include "core/render.h"
#include "util/read_bytes.h"


void opt_list_all(FILE *fp, FILE *render_dest_fp, const ImageFormatHandler *handler, SectionTable *table, OutputRenderer renderer)
{
    for (size_t i = 0; i < table->count; ++i) {
        SectionParserFn parse = find_parser_fn(handler, table->items[i].name);
        if (parse == NULL) continue; // no parser found

        // parse section
        uint8_t *buffer = read_section(fp, table->items[i]); 
        SectionResult result = parse(buffer, table->items[i].data_length, NULL); // TODO: error handling (result.ok)

        // assign section name
        strncpy(result.section_name, table->items[i].name, sizeof(result.section_name)-1);
    
        renderer.render(&result, render_dest_fp);
        free(buffer);
    }

    return;
}


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
    
    // section table

    SectionTable section_table = {0};

    size_t sections_count = format_handler->build_section_table(fp, &section_table);
    if (!sections_count) {
        fprintf(stderr, NO_SECTION_FOUND_ERROR);
        return 1;
    }

    // cli options
    
    if (cli_options.mode == LIST_ALL) {
        opt_list_all(fp, NULL, format_handler, &section_table, text_renderer);
    }

    fclose(fp);
    return 0;
}

