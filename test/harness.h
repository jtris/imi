#ifndef HARNESS_H
#define HARNESS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


extern uint16_t tests_run, tests_failed;


#define ASSERT_EQ_INT(actual, expected) do {\
    tests_run++;\
    if ((actual) != (expected)) {\
        tests_failed++;\
        fprintf(stderr, "[FAIL] %s:%d: expected: %ld, got: %ld\n",\
                __FILE__, __LINE__, (long) (expected), (long) (actual));\
    }\
} while (0)

#define ASSERT_EQ_STRING(actual, expected) do {\
    tests_run++;\
    if (strcmp((actual), (expected)) != 0) {\
        tests_failed++;\
        fprintf(stderr, "[FAIL] %s:%d: expected: \"%s\", got: \"%s\"\n",\
                __FILE__, __LINE__, (expected), (actual));\
    }\
} while (0)

#define RUN_TEST(test_fn) do {\
    test_fn();\
} while (0)


#endif // HARNESS_H
