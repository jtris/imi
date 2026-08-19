#ifndef PNG_FORMAT_H
#define PNG_FORMAT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "core/section.h"
#include "core/format_handler.h"


typedef struct PngContext {
    bool has_color_type;
    uint8_t color_type;
} PngContext;


size_t png_build_section_table(FILE *f, SectionTable *out);


extern const ImageFormatHandler png_handler;

#endif // PNG_FORMAT_H
