#ifndef READ_BYTES_H
#define READ_BYTES_H

#include <stdint.h>
#include <stddef.h>


uint32_t read_u32_be(uint8_t buffer[4], size_t offset);

#endif // READ_BYTES_H
