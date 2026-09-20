#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "read_bytes.h"
#include "core/section.h"

/*
 * read an unsigned 32bit big-endian integer from a buffer
*/
uint32_t read_u32_be(const uint8_t *buffer, size_t offset)
{
    const uint8_t *bytes = buffer + offset;

    return  ((uint32_t) bytes[0] << 24) |
            ((uint32_t) bytes[1] << 16) |
            ((uint32_t) bytes[2] << 8)  |
            ((uint32_t) bytes[3]);
}


uint8_t read_u8_be(const uint8_t *buffer, size_t offset)
{
    return (uint8_t) buffer[offset];
}


uint8_t *read_section(FILE *fp, SectionInfo section_to_read)
{
    fseek(fp, section_to_read.data_offset, SEEK_SET);

    uint8_t *buffer = malloc(section_to_read.data_length * sizeof(uint8_t));
    fread(buffer, 1, section_to_read.data_length, fp);

    return buffer;
}

