#include <stdio.h>
#include <string.h>
#include "render.h"
#include "core/section.h"
#include "section.h"


static void render_text(SectionResult *render_data, FILE *fp);


const OutputRenderer text_renderer = {
    .name = "text",
    .render = render_text,
};


static void render_text(SectionResult *render_data, FILE *fp)
{
    printf("---[ %s ]--------------------\n", render_data->section_name);


    for (size_t i = 0; i < render_data->count; ++i) {
        SectionField item = render_data->items[i];
        printf("%-20s : ", item.label);

        switch (item.type) {
        case FIELD_INT:
            printf("%d\n", item.as_int);
            break;

        case FIELD_STRING:
            printf("%s\n", item.as_string);
            break;

        case FIELD_FRACTION:
            printf("%d/%d\n", item.as_fraction.numerator, item.as_fraction.denominator);
            break;

        case FIELD_INT_ARRAY:
            for (size_t j = 0; j < item.as_int_array.len; ++j) {
                printf("%d", item.as_int_array.arr[j]);
                j == item.as_int_array.len-1 ? printf("\n") : printf(", ");
            }
            break;

        case FIELD_ENUM:
            printf("%s\n", item.as_enum.resolved_label);
            break;

        case FIELD_BYTES:
            for (size_t k = 0; k < item.as_bytes.len; ++k) {
                printf("%02x", item.as_bytes.data[k]);
                k == item.as_bytes.len-1 ? printf("\n") : printf(" ");
            }
            break;
        }

    }

    printf("\n");
    return;
}

