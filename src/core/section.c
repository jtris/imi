#include <stdint.h>
#include "section.h"


void da_append_int(SectionResult *result, const char *label, int64_t value)
{
    SectionField int_field = {
        .label = label,
        .type = FIELD_INT,
        .as_int = value
    };

    DA_APPEND(result, int_field);
}


void da_append_string(SectionResult *result, const char *label, char *string)
{
    SectionField string_field = {
        .label = label,
        .type = FIELD_STRING,
        .as_string = string
    };

    DA_APPEND(result, string_field);
}


void da_append_fraction(SectionResult *result, const char *label, int32_t numerator, int32_t denominator)
{
    SectionField fraction_field = {
        .label = label,
        .type = FIELD_FRACTION,
        .as_fraction = { numerator, denominator }
    };

    DA_APPEND(result, fraction_field);
}


void da_append_int_array(SectionResult *result, const char *label, int64_t *arr, size_t len)
{
    SectionField int_array_field = {
        .label = label,
        .type = FIELD_INT_ARRAY,
        .as_int_array = { arr, len }
    };

    DA_APPEND(result, int_array_field);
}


void da_append_enum(SectionResult *result, const char *label, int64_t raw, const char *resolved_label)
{
    SectionField enum_field = {
        .label = label,
        .type = FIELD_ENUM,
        .as_enum = { raw, resolved_label }
    };

    DA_APPEND(result, enum_field);
}

