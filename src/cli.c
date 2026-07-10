#include <stdio.h>
#include <string.h>
#include "cli.h"


static const OptionSpec options[] = {
    { "list-all",     false,  LIST_ALL     },
    { "list-present", false,  LIST_PRESENT },
    { "list",         true,   LIST         },
};


/*
 * outputs false if there's an unrecognized/invalid option
*/
bool parse_args(int argc, char **argv, Options *out)
{
    bool path_registered = false;

    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        bool recognized_argument = false;

        // if argument isn't prepended with '--' it's the path
        if (strncmp(arg, "--", 2) != 0) {
            if (path_registered) return false;

            out->path = arg;
            path_registered = true;
            continue;
        }

        const char *equals_char = strchr(arg, '='); // pointer to '=' in arg
        
        size_t name_len;
        if (equals_char != NULL) {
            // option with argument
            name_len = (size_t) (equals_char - arg - 2); // -2 to account for '--'
        }
        else {
            // without argument
            name_len = strlen(arg) - 2;
        }

        // try to match one of the argument options with the supplied argument
        for (size_t j = 0; j < sizeof(options)/sizeof(*options); j++) {
            if (strlen(options[j].name) == name_len && strncmp(arg + 2, options[j].name, name_len) == 0) {

                // handle opts with '='
                if (options[j].takes_value) {
                    if (equals_char != NULL) out->chunk_name = equals_char + 1;
                    else return false;
                }

                out->mode = options[j].mode_value;
                recognized_argument = true;
            }
        }

        if (!recognized_argument) return false;
    }
    return true;
}

