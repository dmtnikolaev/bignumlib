#include "main.h"

#include "bignat.h"

void print_help() {
}

void print_version() {
    printf("bignumlib v%s", BIGNUMLIB_VERSION);
}

int main(int argc, char **argv) {
    print_version();

    return 0;
}
