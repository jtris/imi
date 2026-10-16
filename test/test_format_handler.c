#include "harness.h"
#include "core/format_handler.h"


static void test_format_handler_png(void)
{
    uint8_t bytes[] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n', 0, 0, 0, 0 };
    FILE *fp = make_test_file(bytes, sizeof(bytes));
    const ImageFormatHandler *fh = detect_format(fp);
    ASSERT_EQ_STRING(fh->format_name, "PNG");
    fclose(fp);
}


static void test_format_handler_invalid(void)
{
    uint8_t bytes[20] = {0};
    FILE *fp = make_test_file(bytes, sizeof(bytes));
    ASSERT_EQ_INT(detect_format(fp), NULL);
    fclose(fp);
}


void run_format_handler_tests(void)
{
    RUN_TEST(test_format_handler_png);
    RUN_TEST(test_format_handler_invalid);
}
