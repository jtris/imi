#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

#define PRINT_USAGE(stream) fprintf(stream, \
    "Usage:\n" \
    "  imi [filepath] [options]\n\n" \
    "Options:\n" \
    "  (no options selected defaults to --list-all)\n" \
    "  %-30s %s\n" \
    "  %-30s %s\n" \
    "  %-30s %s\n", \
    "--list-all, -a", "List all metadata contents", \
    "--list-present, -p", "List present metadata", \
    "--list=<name>, -l=<name>", "List metadata recognized by <name>" \
)
#define PRINT_INVALID_ARGUMENT_ERROR(stream) do { \
    fprintf(stream, "Error: invalid argument\n"); \
    fprintf(stream, "Try the --help/-h option for more information.\n"); \
} while (0)


typedef enum { HELP, LIST_ALL, LIST_PRESENT, LIST } Mode;

/*
 * used for definitions of individual command-line argument options
*/
typedef struct OptionSpec {
    const char *name;       // full option name prepended with "--"
    const char alias;       // shortened option name prepended with "-"
    bool takes_value;
    Mode mode_value;
} OptionSpec;

/*
 * used to store the user-selected option
*/
typedef struct Options {
    Mode mode;
    char *chunk_name;
    char *path;
} Options;


bool parse_args(int argc, char **argv, Options *out);

#endif // CLI_H

