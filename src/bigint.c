#include "bigint.h"

#include <stdlib.h>
#include <string.h>

#include "bignat.h"
#include "bignumlib-error.h"

void BigInt_new(BigInt **a) {
    BigNat *nat;

    *a = (BigInt *)malloc(sizeof(BigInt));
    if (*a == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    BigNat_new(&nat);
    (*a)->nat = nat;
    (*a)->sign = 0;
}

void BigInt_destroy(BigInt *a) {
}

void BigInt_copy(const BigInt *a, BigInt *copy) {
    BigNat_copy(a->nat, copy->nat);
    copy->sign = a->sign;
}

void BigInt_from_nat(BigInt *a, const BigNat *b) {
}

error_t BigInt_to_nat(const BigInt *a, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_from_string(BigInt *a, const char *str) {
    error_t err;
    int shift;

    shift = 0;

    a->sign = 1;
    if (str[0] == '+' || str[0] == '-') {
        a->sign = str[0] == '+' ? 1 : -1;
        shift = 1;
    }

    err = BigNat_from_string(a->nat, str + shift);
    if (FAIL(err)) {
        return err;
    }

    if (BigNat_is_zero(a->nat)) {
        a->sign = 0;
    }

    return SUCCESS;
}

void BigInt_to_string(const BigInt *a, char **string) {
    size_t str_len, shift;
    char *temp;

    shift = 0;

    if (a->sign == -1) {
        shift = 1;
    }

    str_len = a->nat->size;
    *string = (char *)malloc((str_len + shift + 1) * sizeof(char));
    if (*string == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    BigNat_to_string(a->nat, &temp);
    strcpy(*string + shift, temp);
    if (a->sign == -1) {
        (*string)[0] = '-';
    }

    free(temp);
}

void BigInt_abs(const BigInt *a, BigNat *c) {
}

int BigInt_get_sign(const BigInt *a) {
    return 0;
}

void BigInt_negate(const BigInt *a, BigInt *c) {
}

void BigInt_add(const BigInt *a, const BigInt *b, BigInt *c) {
    if (a->sign == b->sign) {
        c->sign = a->sign;
        BigNat_sum(a->nat, b->nat, c->nat);
    }
    else {
        if (BigNat_compare(a->nat, b->nat) >= 0) {
            c->sign = a->sign;
            BigNat_sub(a->nat, b->nat, c->nat);
        }
        else {
            c->sign = b->sign;
            BigNat_sub(b->nat, a->nat, c->nat);
        }
    }
}

void BigInt_sub(const BigInt *a, const BigInt *b, BigInt *c) {
}

void BigInt_mul(const BigInt *a, const BigInt *b, BigInt *c) {
}

error_t BigInt_div_nat(const BigInt *a, const BigNat *b, BigInt *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_mod_nat(const BigInt *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}
