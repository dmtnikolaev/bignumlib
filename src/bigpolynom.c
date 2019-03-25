#include "bigpolynom.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "bignumlib-error.h"
#include "bigrat.h"

void BigPol_new(BigPol **f) {
    BigRat *r;

    *f = (BigPol *)malloc(sizeof(BigPol));
    if (*f == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    (*f)->size = 1;
    (*f)->coeffs = (BigRat **)malloc((*f)->size * sizeof(BigRat *));
    if ((*f)->coeffs == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    BigRat_new(&r);
    (*f)->coeffs[0] = r;
    (*f)->available_size = 1;
}

void BigPol_destroy(BigPol *f) {
    size_t i;

    if (f == NULL) {
        return;
    }

    if (f->coeffs != NULL) {
        for (i = 0; i < f->available_size; i++) {
            BigRat_destroy(f->coeffs[i]);
        }
        free(f->coeffs);
    }

    free(f);
}

error_t BigPol_from_string(BigPol *f, const char *str) {
    return IE_NOTIMPLEMENTED;
}

void BigPol_resize(BigPol *f, const size_t new_size) {
    size_t i;

    if (new_size <= f->available_size) {
        return;
    }

    f->coeffs = (BigRat **)realloc(f->coeffs, new_size * sizeof(BigRat *));
    if (f->coeffs == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    memset(f->coeffs + f->available_size, 0,
        (new_size - f->available_size) * sizeof(BigRat *));

    f->available_size = new_size;

    for (i = f->size; i < f->available_size; i++) {
        BigRat_new(&f->coeffs[i]);
    }
}

void BigPol_to_string(const BigPol *f, char **str) {
}

void BigPol_sum(const BigPol *f, const BigPol *g, BigPol *h) {
}

void BigPol_sub(const BigPol *f, const BigPol *g, BigPol *h) {
}

void BigPol_mul_scalar(const BigPol *f, const BigRat *c, BigPol *h) {
    size_t i;

    BigPol_resize(h, f->size);

    for(i = 0; i < f->size; i++) {
        BigRat_mul(c, f->coeffs[i], h->coeffs[i]);
    }
    h->size = f->size;
}

void BigPol_mul_expx(const BigPol *f, const BigNat *k, BigPol *h) {
}

void BigPol_get_leading(const BigPol *f, BigRat *a_n) {
}

void BigPol_get_deg(const BigPol *f, BigNat *deg) {
}

void BigPol_fac(const BigPol *f, BigPol *h, BigRat *c) {
}

void BigPol_mul(const BigPol *f, const BigPol *g, BigPol *h) {
}

error_t BigPol_div(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_mod(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

error_t BigPol_gcd(const BigPol *f, const BigPol *g, BigPol *h) {
    return IE_NOTIMPLEMENTED;
}

void BigPol_der(const BigPol *f, BigPol *h) {
}

void BigPol_nmr(const BigPol *f, BigPol *h) {
}

