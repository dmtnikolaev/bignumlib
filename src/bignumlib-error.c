#include "bignumlib-error.h"

#include <stdio.h>
#include <stdlib.h>

char *get_error_message(error_t err) {
    switch (err) {
        case PE_ALLOC:
            return "can't allocate memory";

        case PE_OVERFLOW:
            return "allocated memory is too large";

        case PE_READING:
            return "error while file reading";

        case PE_INVALID_CL_ARGS_COUNT:
            return "invalid command line arguments count";

        case PE_ACTION_NOT_FOUND:
            return "action not found";
        
        case IE_INVALIDPARAM:
            return "(internal) parameter of function is invalid";

        case IE_NOTIMPLEMENTED:
            return "(internal) called function is not implemented";

        default:
            return "unknown";
    }
}

void handle_error(error_t err) {
    if (FAIL(err)) {
        printf("Error: %s. Code: %d", get_error_message(err), (int)err);
    }
}

void handle_critical_error(error_t err) {
    if (FAIL(err)) {
        printf("Critical error: %s. Code: %d", get_error_message(err), (int)err);
        exit((int)err);
    }
}