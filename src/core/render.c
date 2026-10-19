#include <stdio.h>
#include <string.h>
#include "render.h"
#include "cli.h"
#include "core/section.h"
#include "util/unused.h"


static void render_text(SectionResult *render_data, FILE *fp, struct RendererFlags flags);


const OutputRenderer text_renderer = {
    .name = "text",
    .render = render_text,
};


static void indent_text_label(const char *label)
{
    printf("%-20s : ", label);
}


static void render_text(SectionResult *render_data, FILE *fp, struct RendererFlags flags)
{
    // TODO: improve --verbose output
    UNUSED(fp);

    printf("---[ %s ]--------------------\n", render_data->section_name);

    for (size_t i = 0; i < render_data->count; ++i) {
        SectionField item = render_data->items[i];
        indent_text_label(item.label);

        switch (item.type) {
        case FIELD_INT:
            printf("%ld\n", item.as_int);
            break;

        case FIELD_STRING:
            printf("%s\n", item.as_string);
            break;

        case FIELD_FRACTION:
            printf("%d/%d\n", item.as_fraction.numerator, item.as_fraction.denominator);
            break;

        case FIELD_INT_ARRAY:
            for (size_t j = 0; j < item.as_int_array.len; ++j) {
                printf("%ld", item.as_int_array.arr[j]);
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

        case FIELD_RGB_LIST:
            size_t entries_per_line = 8;

            for (size_t i = 0; i < item.as_rgb_list.len/3; ++i) {
                printf("#%02x%02x%02x ",
                       item.as_rgb_list.data[i+0],
                       item.as_rgb_list.data[i+1],
                       item.as_rgb_list.data[i+2]
                );
                
                // limit the number of entries per line
                if ((i+1) % entries_per_line == 0 && i+1 != item.as_rgb_list.len/3) {
                    printf("\n");
                    indent_text_label("");
                }

                // shorten output for non-verbose opt
                if (i > entries_per_line*2-1 && flags.verbose == false) { 
                    printf("... (%zu more entries, use --verbose/-v)", item.as_rgb_list.len/3-i-1);
                    break;
                } 
            }
            printf("\n");
            break;
        }

    }

    printf("\n");
    return;
}

