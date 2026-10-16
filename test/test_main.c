#include "harness.h"
#include <stdint.h>
#include <stdio.h>


void run_format_handler_tests(void);
void run_cli_tests(void);
void run_png_ihdr_tests(void);
void run_png_section_table_builder_tests(void);
void run_png_context_builder_tests(void);


uint16_t tests_run = 0;
uint16_t tests_failed = 0;


int main(void)
{
    run_format_handler_tests();
    run_cli_tests();
    run_png_ihdr_tests();
    run_png_section_table_builder_tests();
    run_png_context_builder_tests();

    if (tests_failed) printf("\n"); // visually separate assert fail messages and results
    printf("[INFO] %d/%d assertions passed\n", tests_run-tests_failed, tests_run);

    return tests_failed == 0 ? 0 : 1;
}
