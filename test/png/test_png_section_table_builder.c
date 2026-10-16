#include <stdint.h>
#include <stdio.h>
#include "harness.h"
#include "core/section.h"
#include "format/png/png_format.h"


static void test_section_table_basic(void)
{
    SectionTable table = {0};
    uint8_t bytes[] = {
        0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n', // PNG signature
        0, 0, 0, 2,                                  // section (1) length
        'a', 'b', 'c', '1',                          //     name
        2, 2, 0, 0, 0, 0,                            //     data, crc
        0, 0, 0, 5,                                  // section (2) length
        'a', 'b', 'c', '2',                          //     name
        5, 5, 5, 5, 5, 0, 0, 0, 0,                   //     data, crc
    };
    
    FILE *fp = make_test_file(bytes, sizeof(bytes));
    size_t sections_found = png_build_section_table(fp, &table);
    
    ASSERT_EQ_INT(sections_found, 2);
    ASSERT_EQ_INT(table.count, 2);
    ASSERT_EQ_STRING(table.items[0].name, "abc1");
    ASSERT_EQ_STRING(table.items[1].name, "abc2");

    fclose(fp);
}


// section table builder should not try to read past IEND
static void test_section_table_IEND(void)
{
    SectionTable table = {0};
    uint8_t bytes[] = {
        0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n',
        0, 0, 0, 0,                                  // minimal IEND section
        'I', 'E', 'N', 'D',
        0, 0, 0, 0,
        0, 0, 0, 1,                                  // dummy unreachable section
        'a', 'b', 'c', 'd',
        1, 0, 0, 0, 0
    };

    FILE *fp = make_test_file(bytes, sizeof(bytes));
    size_t sections_found = png_build_section_table(fp, &table);

    ASSERT_EQ_INT(sections_found, 1);
    ASSERT_EQ_INT(table.count, 1);
    ASSERT_EQ_STRING(table.items[0].name, "IEND");
}


void run_png_section_table_builder_tests(void)
{
    RUN_TEST(test_section_table_basic);
    RUN_TEST(test_section_table_IEND);
}
