#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "harness.h"
#include "core/section.h"
#include "format/png/png_format.h"


static void test_png_context_builder_basic(void)
{

    uint8_t bytes[] = {
        0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n',
        0, 0, 0, 13, 'I', 'H', 'D', 'R',
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        2,                              // color type (truecolor)
        0, 0, 0, 0, 0, 0, 0
    };

    SectionTable table = {0};
    FILE *fp = make_test_file(bytes, sizeof(bytes));
    size_t sections_found = png_build_section_table(fp, &table);
    ASSERT_EQ_INT(sections_found, 1);

    PngContext *png_ctx = png_handler.build_context(fp, &table);
    ASSERT_EQ_INT(png_ctx->has_color_type, true);
    ASSERT_EQ_INT(png_ctx->color_type, 2);

    png_handler.free_context(png_ctx);
}


static void test_png_context_builder_no_ihdr(void)
{
    // two valid sections, but no IHDR => no way to build context
    uint8_t bytes[] = {
        0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n', // PNG signature
        0, 0, 0, 2,                                  // section (1) length
        'a', 'b', 'c', '1',                          //     name
        2, 2, 0, 0, 0, 0,                            //     data, crc
        0, 0, 0, 5,                                  // section (2) length
        'a', 'b', 'c', '2',                          //     name
        5, 5, 5, 5, 5, 0, 0, 0, 0,                   //     data, crc
    };

    SectionTable table = {0};
    FILE *fp = make_test_file(bytes, sizeof(bytes));
    size_t sections_found = png_build_section_table(fp, &table);
    ASSERT_EQ_INT(sections_found, 2);
    PngContext *png_ctx = png_handler.build_context(fp, &table);
    ASSERT_EQ_INT(png_ctx->has_color_type, false);

    png_handler.free_context(png_ctx);
}

void run_png_context_builder_tests(void)
{
    RUN_TEST(test_png_context_builder_basic);
    RUN_TEST(test_png_context_builder_no_ihdr);
}
