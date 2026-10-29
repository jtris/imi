#ifndef PNG_CHUNKS_H
#define PNG_CHUNKS_H

#include <stddef.h>
#include "core/section.h"


SectionResult png_parse_IHDR(const uint8_t *buffer, size_t len, void *ctx);
SectionResult png_parse_PLTE(const uint8_t *buffer, size_t len, void *ctx);
SectionResult png_parse_tEXt(const uint8_t *buffer, size_t len, void *ctx);
SectionResult png_parse_bKGD(const uint8_t *buffer, size_t len, void *ctx);

#endif // PNG_CHUNKS_H
