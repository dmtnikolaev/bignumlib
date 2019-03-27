#include "main.h"

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "actions.h"
#include "bignat.h"
#include "bignumlib-error.h"
#include "utils.h"

int main(int argc, char **argv) {
    error_t err;

    setlocale(LC_ALL, "");

#ifdef DEBUG
    wprintf(L"DEBUG mode\n");
#endif

    // Убираем из аргументов имя приложения.
    argv++;
    argc--;

    err = execute(argc, argv);

    handle_error(err);
    wprintf(L"\n");

#ifdef DEBUG
    if (argc > 0) {
        return err;
    }

    wprintf(L"\n");
    while (1) {
        err = debug_execute();
        handle_error(err);
        
        wprintf(L"\n");
        wprintf(L"\n");
    }
#endif

    return err;
}

error_t execute(int argc, char **argv) {
    error_t err;
    char *action_name, *result;
    int i;

    if (argc < 1) {
        return PE_INVALID_CL_ARGS_COUNT;
    }
    argc--;

    action_name = argv[0];
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

    err = actions_list[i].action(argc, (const char **)argv, &result);
    if (SUCC(err) && result != NULL) {
        wprintf(L"%s", result);
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

error_t debug_execute() {
    error_t err;
    char **argv;
    int argc, i;
    
    err = read_argv_from_user(&argc, &argv);
    if (SUCC(err)) {
        err = execute(argc, argv);
    }

    if (argv == NULL) {
        return err;
    }

    for (i = 0; i < argc; i++) {
        free(argv[i]);
    }

    return err;
}

error_t read_argv_from_user(int *argc, char ***argv) {
    error_t err;
    size_t arg_len;

    arg_len = 0;
    *argc = 0;
    // Выделяем память в массиве под 3 строки, если она не была выделена
    // ранее.
    *argv = (char **)malloc(3 * sizeof(char *));

    err = read_arg_from_stdin(&(*argv)[0], &arg_len, "Enter action name: "); 
    if (FAIL(err)) {
        return err;
    }
    if (arg_len == 0) {
        return PE_INVALID_CL_ARGS_COUNT;
    }

    (*argc)++;

    err = read_arg_from_stdin(&(*argv)[1], &arg_len,
                "Enter first command line argument: "); 
    if (arg_len == 0 || FAIL(err)) {
        return err;
    }
    
    (*argc)++;

    err = read_arg_from_stdin(&(*argv)[2], &arg_len,
                "Enter second command line argument: "); 
    if (arg_len > 0 && SUCC(err)) {
        (*argc)++;
    }

    return err;
}

error_t read_arg_from_stdin(char **arg, size_t *arg_len, const char *prompt) {
    error_t err;
    *arg_len = 0;

    wprintf(L"%s", prompt);
    err = readline(arg, arg_len);
    if (FAIL(err)) {
        return err;
    }

    return SUCCESS;
}
