#include <stdint.h>
#include "harness.h"
#include "../src/core/section.h"
#include "../src/format/png/png_chunks.h"


static void test_ihdr_basic(void)
{
    uint8_t buffer[] = {
        0x00, 0x00, 0x05, 0xdc, // width         : 1500
        0x00, 0x00, 0x03, 0x20, // height        : 800
        0x08,                   // bit depth     : 8
        0x02,                   // color type    : "truecolor"
        0x00,                   // compression   : "inflate/deflate"
        0x00,                   // filter method : "adaptive"
        0x01,                   // interlace     : "Adam7 interlace"
    };

    SectionResult r = png_parse_IHDR(buffer, sizeof(buffer), NULL);

    ASSERT_EQ_INT(r.ok, true);
    ASSERT_EQ_INT(r.count, 7);
    ASSERT_EQ_INT(r.items[0].as_int, 1500);
    ASSERT_EQ_INT(r.items[1].as_int, 800);
    ASSERT_EQ_INT(r.items[2].as_int, 8);
    ASSERT_EQ_STRING(r.items[3].as_enum.resolved_label, "truecolor");
    ASSERT_EQ_STRING(r.items[4].as_enum.resolved_label, "inflate/deflate");
    ASSERT_EQ_STRING(r.items[5].as_enum.resolved_label, "adaptive");
    ASSERT_EQ_STRING(r.items[6].as_enum.resolved_label, "Adam7 interlace");
}


void run_ihdr_tests(void)
{
    RUN_TEST(test_ihdr_basic);
}

