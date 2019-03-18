#include "bigint.h"

error_t BigInt_new(BigInt **a) {
    return IE_NOTIMPLEMENTED;
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

error_t BigInt_to_string(const BigInt *a, char **string) {
    return IE_NOTIMPLEMENTED;
}

void BigInt_abs(const BigInt *a, BigNat *c) {
}

int BigInt_get_sign(const BigInt *a) {
    return 0;
}

void BigInt_negate(const BigInt *a, BigInt *c) {
}

error_t BigInt_add(const BigInt *a, const BigInt *b, BigInt *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_sub(const BigInt *a, const BigInt *b, BigInt *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_mul(const BigInt *a, const BigInt *b, BigInt *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_div_nat(const BigInt *a, const BigNat *b, BigInt *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigInt_mod_nat(const BigInt *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}
