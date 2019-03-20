#include "bigpolynom.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "bignumlib-error.h"
#include "bigrat.h"

error_t BigPol_new(BigPol **f) {
    error_t err;
    BigRat *r;

    *f = (BigPol *)malloc(sizeof(BigPol));
    if (*f == NULL) {
        return PE_ALLOC;
    }

    (*f)->size = 1;
    (*f)->coeffs = (BigRat **)malloc((*f)->size * sizeof(BigRat *));
    if ((*f)->coeffs == NULL) {
        return PE_ALLOC;
    }

    err = BigRat_new(&r);
    if (FAIL(err)) {
        return err;
    }

    (*f)->coeffs[0] = r;
    (*f)->available_size = 1;

    return SUCCESS;
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

error_t BigPol_resize(BigPol *f, const size_t new_size) {
    size_t i;
    error_t err;

    if (new_size <= f->available_size) {
        return SUCCESS;
    }

    f->coeffs = (BigRat **)realloc(f->coeffs, new_size * sizeof(BigRat *));
    if (f->coeffs == NULL) {
        return PE_ALLOC;
    }

    memset(f->coeffs + f->available_size, 0,
        (new_size - f->available_size) * sizeof(BigRat *));

    f->available_size = new_size;

    for (i = f->size; i < f->available_size; i++) {
        err = BigRat_new(&f->coeffs[i]);
        if (FAIL(err)) {
            return err;
        }
    }

    return SUCCESS;
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
    error_t err;
    size_t i;

    BigPol_resize(h, f->size);

    for(i = 0; i < f->size; i++) {
        err = BigRat_mul(c, f->coeffs[i], h->coeffs[i]);
        if (FAIL(err)) {
            return err;
        }
    }
    h->size = f->size;
    return SUCCESS;
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

