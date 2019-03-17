#include "bignumlib-error.h"

#include <stdio.h>

char *get_error_message(error_t err) {
    switch (err) {
        case PE_ALLOC:
            return "can't allocate memory";
        
        case IE_INVALIDPARAM:
            return "(internal) parameter of function is invalid";

        case IE_NOTIMPLEMENTED:
            return "(internal) called function is not implemented";

        default:
            return "unknown";
    }
}

void handle_error(error_t err) {
    printf("Error: %s. Code: %d", get_error_message(err), (int)err);
}
