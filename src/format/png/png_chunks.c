#include <stddef.h>
#include <stdbool.h>
#include "core/section.h"
#include "png_chunks.h"
#include "util/read_bytes.h"


static const char *IHDR_resolve_color_type(uint8_t c)
{
    switch (c) {
        case 0: return "grayscale";
        case 2: return "truecolor";
        case 3: return "indexed";
        case 4: return "grayscale + alpha";
        case 6: return "truecolor + alpha";
        default: return "unrecognized value";
    }
}


static const char *IHDR_resolve_compression_method(uint8_t c)
{
    if (c != 0) return "unrecognized value"; // only 0 is defined
    return "inflate/deflate";
}


static const char *IHDR_resolve_filter_method(uint8_t f)
{
    if (f != 0) return "unrecognized value"; // only 0 is defined
    return "adaptive";
}


static const char *IHDR_resolve_interlace_method(uint8_t i)
{
    switch (i) {
        case 0: return "no interlace";
        case 1: return "Adam7 interlace";
        default: return "unrecognized value";
    }
}


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

    SectionResult result = {0}; // TODO: section result name assignment
    result.ok = true;

    if (len < 13) {
        result.ok = false;
        result.error = "IHDR chunk is too short.";
        return result;
    }

    da_append_int(&result, "width", read_u32_be(buffer, 0));
    da_append_int(&result, "height", read_u32_be(buffer, 4));
    da_append_int(&result, "bit depth", read_u8_be(buffer, 8));

    uint8_t color = read_u8_be(buffer, 9);
    da_append_enum(&result, "color type", color, IHDR_resolve_color_type(color));

    uint8_t compression = read_u8_be(buffer, 10);
    da_append_enum(&result, "compression method", compression, IHDR_resolve_compression_method(compression));

    uint8_t filter = read_u8_be(buffer, 11);
    da_append_enum(&result, "filter method", filter, IHDR_resolve_filter_method(filter));

    uint8_t interlace = read_u8_be(buffer, 12);
    da_append_enum(&result, "interlace method", interlace, IHDR_resolve_interlace_method(interlace));

    return result;
}

