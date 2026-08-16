#ifndef READ_BYTES_H
#define READ_BYTES_H

#include <stdint.h>
#include <stddef.h>


uint32_t read_u32_be(const uint8_t *buffer, size_t offset);
uint8_t read_u8_be(const uint8_t *buffer, size_t offset);

#endif // READ_BYTES_H
