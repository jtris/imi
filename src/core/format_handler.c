#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "format_handler.h"
#include "format/png/png_format.h"


/*
 * register all format handlers here
*/
static const ImageFormatHandler *format_registry[] = {
    &png_handler,
};

static const size_t format_registry_count = sizeof(format_registry) / sizeof(*format_registry);


/*
 * returns the appropriate format handler if the format is recognized by its signature (magic bytes)
 * otherwise NULL
*/
const ImageFormatHandler *detect_format(FILE *fp)
{
    uint8_t prefix_buffer[SIGNATURE_BUFFER_SIZE] = {0};
    size_t bytes_read = fread(&prefix_buffer, 1, SIGNATURE_BUFFER_SIZE, fp);

    if (bytes_read < SIGNATURE_BUFFER_SIZE) return NULL;

    for (size_t i = 0; i < format_registry_count; ++i) {
        const ImageFormatHandler *current_format = format_registry[i];
        SignatureBytes current_signature = current_format->signature;

        if (current_signature.offset + current_signature.len > SIGNATURE_BUFFER_SIZE) continue;
        if (memcmp(prefix_buffer + current_signature.offset, current_signature.bytes, current_signature.len) == 0)
            return current_format;
    }

    return NULL;
}


SectionParserFn find_parser_fn(const ImageFormatHandler *handler, const char *section_name)
{
    for (size_t i = 0; i < handler->parser_count; ++i) {
        if (strcmp(handler->parsers[i].name, section_name) == 0)
            return handler->parsers[i].function;
    }

    return NULL;
}


