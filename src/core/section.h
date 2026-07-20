#ifndef SECTION_H
#define SECTION_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef enum { FIELD_INT, FIELD_STRING, FIELD_FRACTION,
               FIELD_INT_ARRAY, FIELD_ENUM, FIELD_BYTES } FieldType;

/*
 * represents an individual field belonging to a section
 */
typedef struct SectionField {
    const char *label;
    FieldType type;

    union { // each field can only store one 
        int64_t as_int;
        char *as_string;
        struct { int32_t numerator, denominator; } as_fraction;
        struct { int64_t *arr; size_t len; } as_int_array;
        struct { int64_t raw; char *resolved_label; } as_enum; // raw int representing a lookup table label
        struct { uint8_t *data; size_t len; } as_bytes;
    };
} SectionField;

/*
 * the return value of a section parser function
 */
typedef struct SectionResult {
    char section_name[16];
    SectionField *fields;
    size_t field_count;
    size_t field_capacity;
    bool ok;
    char *error;            // error message
} SectionResult;

/*
 * section parser
 * `buffer` contains the entire section, `ctx` is any additional context required by
 * a specific parser
 */
typedef SectionResult (*SectionParserFn) (const uint8_t *buffer, size_t len, void *ctx);

 
typedef struct SectionParserEntry {
    const char *name;
    SectionParserFn function;
} SectionParserEntry;

/*
 * used for building the SectionTable
 */
typedef struct SectionInfo {
    char name[16];
    long data_offset;
    long data_length;
} SectionInfo;


typedef struct SectionTable {
    SectionInfo *items;
    size_t count;
    size_t capacity;
} SectionTable;


#endif // SECTION_H
