#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "read_bytes.h"
#include <stdio.h>

/*
 * read an unsigned 32bit big-endian integer from a buffer
*/
uint32_t read_u32_be(const uint8_t *buffer, size_t offset)
{
    uint8_t *bytes = buffer + offset;

    return  ((uint32_t) bytes[0] << 24) |
            ((uint32_t) bytes[1] << 16) |
            ((uint32_t) bytes[2] << 8)  |
            ((uint32_t) bytes[3]);
}


uint8_t read_u8_be(const uint8_t *buffer, size_t offset)
{
    return (uint8_t) buffer[offset];
}

