#include <stddef.h>
#include <stdbool.h>
#include "core/section.h"
#include "png_chunks.h"
#include "core/section.h"
#include "util/read_bytes.h"


SectionResult png_parse_IHDR(const uint8_t *buffer, size_t len, void *ctx) 
{
    /*
    Width:              4 bytes
    Height:             4 bytes
    Bit depth:          1 byte
    Color type:         1 byte
    Compression method: 1 byte
    Filter method:      1 byte
    Interlace method:   1 byte
    */
    
    SectionResult result = {
        .section_name = "IHDR",
        .items = NULL,
        .count = 0,
        .capacity = 0,
        .ok = true,
        .error = NULL
    };

    SectionField width = {
        .label = "width",
        .type = FIELD_INT,
        .as_int = read_u32_be(buffer, 0),
    };
    DA_APPEND((&result), width);

    SectionField height = {
        .label = "height",
        .type = FIELD_INT,
        .as_int = read_u32_be(buffer, 4),
    };
    DA_APPEND((&result), height);

    SectionField bit_depth = {
        .label = "bit depth",
        .type = FIELD_INT,
        .as_int = read_u8_be(buffer, 8),
    };
    DA_APPEND((&result), bit_depth);

    SectionField color_type = {
        .label = "color type",
        .type = FIELD_ENUM,
        .as_enum = {
            .raw = read_u8_be(buffer, 9),
            .resolved_label = "TMP" // TODO: label resolution
        },
    };
    DA_APPEND((&result), color_type);

    // compression method: 1 byte
    SectionField compression_method = {
        .label = "compression method",
        .type = FIELD_ENUM,
        .as_enum = {
            .raw = read_u8_be(buffer, 10),
            .resolved_label = "TMP" // TODO: label resolution
        },
    };
    DA_APPEND((&result), compression_method);

    SectionField filter_method = {
        .label = "filter method",
        .type = FIELD_ENUM,
        .as_enum = {
            .raw = read_u8_be(buffer, 11),
            .resolved_label = "TMP" // TODO: label resolution
        },
    };
    DA_APPEND((&result), filter_method);

    SectionField interlace_method = {
        .label = "interlace method",
        .type = FIELD_ENUM,
        .as_enum = {
            .raw = read_u8_be(buffer, 12),
            .resolved_label = "TMP" // TODO: label resolution
        },
    };
    DA_APPEND((&result), interlace_method);

    return result;
}

