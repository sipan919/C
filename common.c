#include <stdio.h>

#include "common.h"


enum Boolean process_error(const enum Error error_code)
{
    fprintf(stderr, "Error: %d\n", error_code);

    return FALSE;
}

