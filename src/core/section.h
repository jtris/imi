#ifndef SECTION_H
#define SECTION_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define DA_APPEND(xs, x)\
    do {\
        if (xs->count >= xs->capacity) {\
            if (xs->capacity == 0) xs->capacity = 16;\
            else xs->capacity *= 2;\
            xs->items = realloc(xs->items, xs->capacity*sizeof(*xs->items));\
        }\
        xs->items[xs->count++] = x;\
    } while(0)


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
    SectionField *items;
    size_t count;
    size_t capacity;
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
    size_t data_offset;
    size_t data_length;
} SectionInfo;


typedef struct SectionTable {
    SectionInfo *items;
    size_t count;
    size_t capacity;
} SectionTable;

#endif // SECTION_H
