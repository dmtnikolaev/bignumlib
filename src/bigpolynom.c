#include "bigpolynom.h"

#include <stddef.h>

#include "bignumlib-error.h"
#include "bigrat.h"

error_t BigPol_new(BigPol **f) {
    return IE_NOTIMPLEMENTED;
}

void BigPol_destroy(BigPol *f) {
}

error_t BigPol_resize(BigPol *f, const size_t new_size) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_from_string(BigPol *f, const char *str) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_to_string(const BigPol *f, char **str) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_sum(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_sub(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_mul_scalar(const BigPol *f, const BigRat *c, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_mul_expx(const BigPol *f, const BigNat *k, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_get_leading(const BigPol *f, BigRat *a_n) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_get_deg(const BigPol *f, BigNat *deg) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_fac(const BigPol *f, BigPol *h, BigRat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_mul(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_div(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

