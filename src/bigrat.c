#include "bigrat.h"

#include "bigint.h"
#include "bignat.h"
#include "bignumlib-error.h"

void BigRat_new(BigRat **a) {
}

void BigRat_destroy(BigRat *a) {
}

void BigRat_copy(const BigRat *a, BigRat *copy) {
    BigInt_copy(a->num, copy->num);
    BigNat_copy(a->denom, copy->denom);
}

void BigRat_from_int(BigRat *a, const BigInt *integ) {
}

error_t BigRat_to_int(const BigRat *a, BigInt *integ) {
    return IE_NOTIMPLEMENTED;
}

error_t BigRat_from_string(BigRat *a, const char *str) {
    return IE_NOTIMPLEMENTED;
}

void BigRat_to_string(const BigRat *a, char **str) {
}

void BigRat_reduce(BigRat *a) {
}

int BigRat_is_int(const BigRat *a) {
    return 0;
}

void BigRat_sum(const BigRat *a, const BigRat *b, BigRat *c) {
}

void BigRat_sub(const BigRat *a, const BigRat *b, BigRat *c) {
}

void BigRat_mul(const BigRat *a, const BigRat *b, BigRat *c) {
}

error_t BigRat_div(const BigRat *a, const BigRat *b, BigRat *c) {
    return IE_NOTIMPLEMENTED;
}

