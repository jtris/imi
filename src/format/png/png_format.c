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

static void *png_build_context(FILE *fp, const SectionTable *table);
static void png_free_context(void *ctx);


static const uint8_t png_signature_bytes[] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};

static const SectionParserEntry png_parsers[] = {
    { "IHDR", png_parse_IHDR },
    { "PLTE", png_parse_PLTE }
};

const ImageFormatHandler png_handler = {
    .format_name = "PNG",
    .signature = {
        .bytes = png_signature_bytes, 
        .len = sizeof(png_signature_bytes),
        .offset = 0
    },
    .build_section_table = png_build_section_table,
    .parsers = png_parsers,
    .parser_count = sizeof(png_parsers)/sizeof(*png_parsers),
    .build_context = png_build_context,
    .free_context = png_free_context,
};


static void *png_build_context(FILE *fp, const SectionTable *table)
{
    PngContext *ctx = malloc(sizeof(*ctx));
    *ctx = (PngContext) {0};

    for (size_t i = 0; i < table->count; ++i) {
        if (strcmp("IHDR", table->items[i].name) != 0) continue;

        // read header contents and directly read the `color type` byte
        // it's the only piece of information other png chunks might need
        uint8_t header_buffer[13];
        fseek(fp, table->items[i].data_offset, SEEK_SET);
        fread(header_buffer, 1, sizeof(header_buffer), fp); 
        ctx->color_type = read_u8_be(header_buffer, 9);
        ctx->has_color_type = true;
        break;
    }

    return ctx;
}


static void png_free_context(void *ctx) { free(ctx); }


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

        DA_APPEND(out, info);
        section_count++;

        if (strcmp(info.name, "IEND") == 0) break; // empty end chunk
        fseek(fp, 4 + length, SEEK_CUR); // skip current chunk's CRC and data
                                         // file pointer ends up at the start of the next chunk

    }
    return section_count;
}

