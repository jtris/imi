#ifndef FORMAT_HANDLER_H
#define FORMAT_HANDLER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "section.h"

#define SIGNATURE_BUFFER_SIZE 50
#define UNRECOGNIZED_FORMAT_ERROR "Error: Unrecognized or not supported file format\n"
#define NO_SECTION_FOUND_ERROR "Error: No sections found despite recognizing a valid format signature.\n"\
                               "       The provided file might be corrupted or truncated.\n"

/*
 * used to store "signature/magic" bytes for each format
*/
typedef struct SignatureBytes {
    const uint8_t *bytes;
    size_t len;
    size_t offset;
} SignatureBytes;

/*
 * an interface for each format
*/
typedef struct ImageFormatHandler {
    const char *format_name;
    SignatureBytes signature;
    size_t (*build_section_table) (FILE *f, SectionTable *out);
    const SectionParserEntry *parsers;
    size_t parser_count;
} ImageFormatHandler;


const ImageFormatHandler *detect_format(FILE *fp);

#endif // FORMAT_HANDLER_H
