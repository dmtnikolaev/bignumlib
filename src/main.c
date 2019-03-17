#include "main.h"

#include "bignat.h"

void print_help() {
}

void print_version() {
    printf("bignumlib v%s", BIGNUMLIB_VERSION);
}

int main(int argc, char **argv) {
    print_version();
    puts("");
    
    // В данный момент еще не реализован интерфейс взаимодействия с программой.
    // Поэтому для тестирования функционала можно добавить сюда простые вызовы
    // написанных Вами функций. Например:

    BigNat *a, *b, *c;
    char *res;
    error_t err;
    err = BigNat_new(&a);
    err = BigNat_new(&b);
    err = BigNat_new(&c);
    err = BigNat_from_string(a, "12345679012345679");
    err = BigNat_from_string(b, "9");
    err = BigNat_mul(a, b, c);
    err = BigNat_to_string(c, &res);
    printf("Result: %s", res); // 111111111111111111

    handle_error(err);
    return 0;
}
