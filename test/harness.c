#include <stdio.h>
#include <stdint.h>
#include "harness.h"


FILE *make_test_file(const uint8_t *bytes, size_t len)
{
    FILE *fp = tmpfile();
    fwrite(bytes, 1, len, fp);
    rewind(fp);
    return fp;
}

