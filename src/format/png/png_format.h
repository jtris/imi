#ifndef PNG_FORMAT_H
#define PNG_FORMAT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "core/section.h"
#include "core/format_handler.h"


extern const ImageFormatHandler png_handler;

bool png_build_section_table(FILE *f, SectionTable *out);


#endif // PNG_FORMAT_H
