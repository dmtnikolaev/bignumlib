#include "bigint.h"

#include <stdlib.h>

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

void BigInt_destroy(BigNat *a) {   
}

void BigInt_from_nat(BigInt *a, const BigNat *b) {
}

error_t BigInt_to_nat(const BigInt *a, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_from_string(BigInt *a, const char *str) {
    return IE_NOTIMPLEMENTED;
}

void BigInt_to_string(const BigInt *a, char **string) {
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
