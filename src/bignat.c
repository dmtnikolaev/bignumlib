#include "bignat.h"

#include <stdlib.h>
#include <string.h>

#include "bignumlib-error.h"
#include "utils.h"

error_t BigNat_new(BigNat **a) {
    *a = (BigNat *)malloc(sizeof(BigNat));
    if (*a == NULL) {
        return PE_ALLOC;
    }

    // Выделяем память только под одну цифру - 0.
    (*a)->size = 1;
    (*a)->digits = (digit *)malloc((*a)->size * sizeof(digit));
    if ((*a)->digits == NULL) {
        return PE_ALLOC;
    }

    (*a)->digits[0] = 0;
    (*a)->available_size = (*a)->size;
    
    return SUCCESS;
}

void BigNat_destroy(BigNat *a) {
}

error_t BigNat_resize(BigNat *a, size_t new_size) {
    if (new_size <= a->available_size) {
        return SUCCESS;
    }

    a->available_size = new_size;
    a->digits = (digit *)realloc(a->digits, new_size);
    if (a->digits == NULL) {
        return PE_ALLOC;
    }

    // Обнуляем только что добавленные разряды.
    memset(a->digits + a->available_size, 0,
        (new_size - a->available_size) * sizeof(digit));

    return SUCCESS;
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
    size_t i;

    if (a->size > b->size) {
        return 1;
    }
    else if (a->size < b->size) {
        return -1;
    }
    else {
        for (i = a->size-1; i >= 0; i--) {
            if (a->digits[i] == b->digits[i]) {
                continue;
            }

            return a->digits[i] > b->digits[i] ? 1 : -1;
        }
        return 0;
    }
}

int BigNat_is_zero(const BigNat *a) {
    return 0;
}

error_t BigNat_add_one(const BigNat *a, BigNat *c) {
    return IE_NOTIMPLEMENTED;
}

error_t BigNat_sum(const BigNat *a,const  BigNat *b, BigNat *c) {
    error_t err;
    digit a_d, b_d, c_d_carry;
    size_t i;

    err = BigNat_resize(c, MAX(a->size, b->size) + 1);
    if (FAIL(err)) {
        return err;
    }

    c_d_carry = 0;
    for (i = 0; i < c->available_size; i++) {
        a_d = i >= a->available_size ? 0 : a->digits[i];
        b_d = i >= b->available_size ? 0 : b->digits[i];
        
        c_d_carry += a_d + b_d;
        c->digits[i] = c_d_carry % 10;
        c_d_carry /= 10;
    }

    c->size = i;

    return SUCCESS;
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
