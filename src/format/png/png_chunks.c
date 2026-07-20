#include <stddef.h>
#include <stdbool.h>
#include "core/section.h"
#include "png_chunks.h"
#include "core/section.h"


SectionResult png_parse_IHDR (const uint8_t *buffer, size_t len, void *ctx) 
{
    // TODO
    SectionResult tmp = { "tmp", NULL , 0, 0, true, 0};
    return tmp;
}

