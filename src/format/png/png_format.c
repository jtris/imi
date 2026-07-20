#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "png_format.h"
#include "png_chunks.h"
#include "core/section.h"
#include "core/format_handler.h"


static const uint8_t png_signature_bytes[] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};

static const SectionParserEntry png_parsers[] = {
    { "IHDR", png_parse_IHDR },
};

const ImageFormatHandler png_handler = {
    .format_name = "PNG",
    .signature = {
        .bytes = png_signature_bytes, 
        .len = sizeof(png_signature_bytes),
        .offset = 0 },
    .build_section_table = png_build_section_table,
    .parsers = png_parsers,
    .parser_count = sizeof(png_parsers)/sizeof(*png_parsers),
};


bool png_build_section_table(FILE *f, SectionTable *out)
{
    return false; // TODO
}

