#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

#define USAGE \
    "Usage:\n" \
    "  imi [filepath] [options]\n\n" \
    "Options:\n" \
    "  (no options selected defaults to --list-all)\n" \
    "  --list-all, -a                 Show fields for every section that has a registered parser\n" \
    "  --list-present, -p             List every section found in the file\n" \
    "  --list=<name>, -l=<name>       Show the decoded fields for one section (e.g. --list=IHDR)\n" \
    "  --help, -h                     Print help\n"

#define INVALID_ARGUMENT_ERROR \
    "Error: invalid argument\n" \
    "Try the --help/-h option for more information.\n"

#define FILE_ACCESS_ERROR "Error: Could not open file\n"


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
    char *section_name;
    char *path;
} Options;


bool parse_args(int argc, char **argv, Options *out);

#endif // CLI_H

