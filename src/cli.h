#ifndef CLI_H
#define CLI_H

#define USAGE "Usage:\n  imi [filepath] [options]\n\nOptions:\n  \
    (no options selected defaults to --list-all)\n  \
    --list-all\t\tList all metadata contents\n  \
    --list-present\t\tList present metadata\n  \
    --list=name\t\tList metadata recognized by \"name\"\n"
#define INVALID_ARGUMENTS "Error: invalid argument(s). See available options.\n"


typedef enum { LIST_ALL, LIST_PRESENT, LIST } Mode;

/*
 * used for definitions of individual command-line argument options
*/
typedef struct OptionSpec {
    const char *name;
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

