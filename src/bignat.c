#include "bignat.h"

error_t BigNat_new(BigNat **a) {
    return IE_NOTIMPLEMENTED;
}

void BigNat_destroy(BigNat *a) {
}

error_t BigNat_resize(BigNat *a, size_t new_size) {
    return IE_NOTIMPLEMENTED;
}

int BigNat_is_number(const BigNat *a) {
    return 0;
}

error_t BigNat_from_string(BigNat *a, const char *str) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_to_string(const BigNat *a, char **result) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_zero(BigNat **zero) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_one(BigNat **one) {
    return IE_NOTIMPLEMENTED;
}

int BigNat_compare(const BigNat *a, const BigNat *b) {
    return 0;
}

int BigNat_is_zero(const BigNat *a) {
    return 0;
}

error_t BigNat_add_one(const BigNat *a, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_sum(const BigNat *a,const  BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_sub(const BigNat *a,const  BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_mul_by_digit(const BigNat *a, digit d, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_mul_by_exp10(const BigNat *a, int k, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_mul(const BigNat *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_sub_proportional(const BigNat *a, const BigNat *b, digit d,
                                BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_div_ordered_digit(const BigNat *a, const BigNat *b,
                                 digit *d) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_div(const BigNat *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_mod(const BigNat *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_gcf(const BigNat *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_lcm(const BigNat *a, const BigNat *b, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}
