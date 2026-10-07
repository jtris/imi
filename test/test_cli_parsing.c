#include <stdbool.h>
#include <stdio.h>
#include "harness.h"
#include "cli.h"

#define PARSE_ARGS(argv, out) parse_args((int) sizeof(argv)/sizeof(argv[0]), argv, &out)


// list all should be the default option when none is chosen
static void test_cli_default_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "path" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, true);
    ASSERT_EQ_INT(out.mode, LIST_ALL); 
    ASSERT_EQ_STRING(out.path, "path");
}


// cli option which doesn't take a value
static void test_cli_no_value_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "--list-present", "path"};
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, true);
    ASSERT_EQ_INT(out.mode, LIST_PRESENT);
    ASSERT_EQ_STRING(out.path, "path");
}


// cli option which requires a value
static void test_cli_value_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "-l=x", "path"};
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, true);
    ASSERT_EQ_INT(out.mode, LIST);
    ASSERT_EQ_STRING(out.section_name, "x");
    ASSERT_EQ_STRING(out.path, "path");
}


// only option which doesn't require a path to a file to be present
static void test_cli_help(void)
{
    Options out = {0};
    char *argv[] = { "", "-h" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, true);
    ASSERT_EQ_INT(out.mode, HELP);
}


// no path given by the user (not required to be valid)
static void test_cli_no_path(void)
{
    Options out = {0};
    char *argv[] = { "", "-l" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


static void test_cli_invalid_short_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "path", "-1" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


static void test_cli_invalid_long_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "path", "--invalidlong_" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


// no value given to value option (--opt=value), emtpy is valid (--opt=)
static void test_cli_no_value_given_to_value_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "path", "--list" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


static void test_cli_no_args(void)
{
    Options out = {0};
    char *argv[] = { "" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


static void test_cli_repeated_short_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "image/.../path/", "-a", "-l=x" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


static void test_cli_repeated_long_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "image/.../path/", "--list-all", "--list=x", "--list-present" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


static void test_cli_repeated_same_opt(void)
{
    Options out = {0};
    char *argv[] = { "", "image/.../path/", "--list-present", "--list-present" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


// user supplied more arguments that may be the path
static void test_cli_multiple_paths(void)
{
    Options out = {0};
    char *argv[] = { "", "image/.../path/", "image/.../path2/" };
    bool ok = PARSE_ARGS(argv, out);
    ASSERT_EQ_INT(ok, false);
}


void run_cli_tests(void)
{
    RUN_TEST(test_cli_default_opt);
    RUN_TEST(test_cli_no_value_opt);
    RUN_TEST(test_cli_value_opt);
    RUN_TEST(test_cli_help);

    RUN_TEST(test_cli_no_path);
    RUN_TEST(test_cli_invalid_short_opt);
    RUN_TEST(test_cli_invalid_long_opt);
    RUN_TEST(test_cli_no_value_given_to_value_opt);
    RUN_TEST(test_cli_no_args);
    RUN_TEST(test_cli_repeated_short_opt);
    RUN_TEST(test_cli_repeated_long_opt);
    RUN_TEST(test_cli_repeated_same_opt);
    RUN_TEST(test_cli_multiple_paths);
}

