#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "png_chunks.h"
#include "format/png/png_format.h"
#include "core/section.h"
#include "png_format.h"
#include "util/read_bytes.h"
#include "util/unused.h"


/*
 * IHDR
 */

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
    UNUSED(ctx);

    /*
    Width:              4 bytes
    Height:             4 bytes
    Bit depth:          1 byte
    Color type:         1 byte
    Compression method: 1 byte
    Filter method:      1 byte
    Interlace method:   1 byte
    */

    SectionResult result = {0};
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

/*
 * PLTE
*/

SectionResult png_parse_PLTE(const uint8_t *buffer, size_t len, void *ctx)
{
    UNUSED(ctx);
    SectionResult result = {0};
    result.ok = true;

    // PLTE's length has to be divisible by 3, contains 0 < rgb entries < 257
    if (len % 3 != 0 || len == 0 || len > 256*3) {
        result.ok = false;
        result.error = "PLTE chunk has an invalid length";
        return result;
    }

    da_append_rgb_list(&result, "palette colors", buffer, len);

    return result;
}

/*
 * tEXt
*/

SectionResult png_parse_tEXt(const uint8_t *buffer, size_t len, void *ctx)
{
    UNUSED(ctx);
    SectionResult result = {0};
    result.ok = true;

    if (len < 3) { // has to have at least a label (>= 1 byte) + 0x00 + text (>= 1 byte)
        result.ok = false;
        result.error = "tEXt chunk too short";
        return result;
    }

    const char *null_character = strchr((char *) buffer, '\0');
    if (null_character == NULL) {
        result.ok = false;
        result.error = "tEXt chunk missing a null character: unable to detect keyword and text";
        return result;
    }
    
    const char *label = (char *) buffer;
    const char *text = null_character + 1;
    size_t text_length = len - (size_t) (text - label);
    da_append_string_slice(&result, label, text, text_length); 

    return result;
}

/*
* bKGD
*/


void set_bKGD_invalid_length_result(SectionResult *r)
{
    r->ok = false;
    r->error = "bKGD chunk has an invalid length";
}


SectionResult png_parse_bKGD(const uint8_t *buffer, size_t len, void *ctx)
{
    SectionResult result = {0};
    result.ok = true;

    if (!((PngContext *) ctx)->has_color_type) {
        result.ok = false;
        result.error = "Could not parse bKGD chunk: failed to read image color type";
        return result;
    }

    uint8_t color_type = ((PngContext *) ctx)->color_type;

    switch (color_type) {
    // indexed color: contains the palette index (1 byte)
    case 3:
        if (len != 1) {
            set_bKGD_invalid_length_result(&result);
            return result;
        }
        da_append_int(&result, "palette index", read_u8_be(buffer, 0));
        break;

    // grayscale with/without alpha: contains a u16 integer gray level
    case 0: case 4: 
        if (len != 2) {
            set_bKGD_invalid_length_result(&result);
            return result;
        }
        da_append_int(&result, "gray level", read_u16_be(buffer, 0));
        break;

    // truecolor with/without alpha: 3 u16 integers representing r, g, b
    case 2: case 6: 
        if (len != 6) {
            set_bKGD_invalid_length_result(&result);
            return result;
        }
        da_append_int(&result, "red value",   read_u16_be(buffer, 0));
        da_append_int(&result, "green value", read_u16_be(buffer, 2));
        da_append_int(&result, "blue value",  read_u16_be(buffer, 4));
        break;
    }

    return result;
}

// NEXT: cHRM, gAMA, pHYs, sBIT, tRNS, tIME, sRGB, eXIf, zTXt, iTXt
