#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cli.h"


static const OptionSpec options[] = {
    { "help",         'h', false,  HELP         },
    { "list-all",     'a', false,  LIST_ALL     },
    { "list-present", 'p', false,  LIST_PRESENT },
    { "list",         'l', true,   LIST         }
};


/*
 * outputs false if there's an unrecognized/invalid option
*/
bool parse_args(int argc, char **argv, Options *out)
{
    bool path_registered = false;
    bool mode_registered = false;
    bool is_long_opt = false;

    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        bool recognized_argument = false;

        // if argument isn't prepended with '-' nor '--' it's the path
        if (strncmp(arg, "-", 1) != 0) {
            if (path_registered) return false;

            out->path = arg;
            path_registered = true;
            continue;
        }

        // distinguish between '-' and '--' options
        if (strncmp(arg, "--", 2) == 0) is_long_opt = true;

        const char *equals_char = strchr(arg, '='); // pointer to '=' in arg
        

        size_t name_len;
        if (is_long_opt) {
            // long option with argument
            if (equals_char != NULL) name_len = (size_t) (equals_char - arg - 2);

            // without argument
            else name_len = strlen(arg) - 2;
        }

        // try to match one of the argument options with the supplied argument
        for (size_t j = 0; j < sizeof(options)/sizeof(*options); j++) {
            if ( (strlen(options[j].name) == name_len && strncmp(arg + 2, options[j].name, name_len) == 0) 
                || (!is_long_opt && *(arg+1) == options[j].alias)) {
            
                // handle opts with '='
                if (options[j].takes_value) {
                    if (equals_char != NULL) out->chunk_name = equals_char + 1;
                    else return false;
                }

                out->mode = options[j].mode_value;
                mode_registered = true;
                recognized_argument = true;
            }
        }

        if (!recognized_argument) return false;
    }

    // providing no options will default to --list-all
    if (!mode_registered) out->mode = LIST_ALL;

    // only --help/-h can go without the path
    if (out->mode != HELP) return path_registered;
    return true;
}

