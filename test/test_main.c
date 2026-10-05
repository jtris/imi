#include "harness.h"
#include <stdint.h>
#include <stdio.h>


void run_ihdr_tests(void);


uint16_t tests_run = 0;
uint16_t tests_failed = 0;


int main(void)
{
    run_ihdr_tests();

    if (tests_failed) printf("\n"); // visually separate assert fail messages and results
    printf("%d/%d tests passed\n", tests_run-tests_failed, tests_run);

    return tests_failed == 0 ? 0 : 1;
}
