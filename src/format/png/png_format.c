#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "png_chunks.h"
#include "png_format.h"
#include "core/section.h"
#include "core/format_handler.h"
#include "util/read_bytes.h"


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


size_t png_build_section_table(FILE *fp, SectionTable *out)
{
    size_t section_count = 0;
    fseek(fp, sizeof(png_signature_bytes), SEEK_SET); // skip signature
    
    while (1) {
        uint8_t buffer[8];
        if (fread(buffer, 1, 8, fp) != 8) break; // end of file (if we read less than 8 bytes)
        
        uint32_t length = read_u32_be(buffer, 0); // 4 "length" bytes followed by 4 "type code / identifier" bytes 

        SectionInfo info = {
            .data_offset = ftell(fp),
            .data_length = length,
        };
        memcpy(info.name, buffer+4, 4);
        info.name[4] = 0; // add null terminator

        SECTION_TABLE_APPEND(out, info);
        section_count++;

        if (strcmp(info.name, "IEND") == 0) break; // empty end chunk
        fseek(fp, 4 + length, SEEK_CUR); // skip current chunk's CRC and data
                                         // file pointer ends up at the start of the next chunk

    }
    return section_count;
}

