#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actions.h"
#include "bignat.h"
#include "bignumlib-error.h"

int main(int argc, const char **argv) {
    error_t err;

    // Убираем из аргументов имя приложения.
    argv++;
    argc--;

    err = execute(argc, argv);

    handle_error(err);
    return err;
}

error_t execute(int argc, const char **argv) {
    error_t err;
    char *action_name, *result;
    int i;

    if (argc < 1) {
        return PE_INVALID_CL_ARGS_COUNT;
    }
    argc--;

    action_name = (char*)argv[0];
    remove_dashes(action_name);

    err = find_action(action_name, &i);
    if (FAIL(err)) {
        return err;
    }
    argv++;

    result = NULL;
    if (actions_list[i].param_count != argc) {
        return PE_INVALID_CL_ARGS_COUNT;
    }

    err = actions_list[i].action(argc, argv, &result);
    if (SUCC(err)) {
        printf(result);
    }

    free(result);
    return err;
}

void remove_dashes(char *str) {
    while (*str == DASH) {
        str++;
    }
}

error_t find_action(const char *name, int *i) {
    int j;

    for (j = 0; j < ACTIONS_LEN_MAX; j++) {
        if (strcmp(name, actions_list[j].name) == 0) {
            *i = j;
            return SUCCESS;
        }
    }

    return PE_ACTION_NOT_FOUND;
}