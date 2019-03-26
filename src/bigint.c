#include "bigint.h"

#include <ctype.h>
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
    if (a != NULL) {
        BigNat_destroy(a->nat);
        a->sign = 0;
    }
    free(a);
}

void BigInt_copy(const BigInt *a, BigInt *copy) {
    BigNat_copy(a->nat, copy->nat);
    copy->sign = a->sign;
}

void BigInt_from_nat(BigInt *a, const BigNat *b) {
    BigNat_copy(b, a->nat);
    a->sign = !BigNat_is_zero(b);
}

error_t BigInt_to_nat(const BigInt *a, BigNat *c) {
    if (a->sign == -1) {
        return IE_INVALIDPARAM;
    }
    BigInt_abs(a, c);
    return SUCCESS;
}

error_t BigInt_from_string(BigInt *a, const char *str) {
    error_t err;
    int shift;

    shift = 0;
    while (isspace(str[shift])) {
        shift++;
    }

    a->sign = 1;
    if (str[shift] == '+' || str[shift] == '-') {
        a->sign = str[shift] == '+' ? 1 : -1;
        shift++;
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
    BigNat_resize(c, a->nat->size);
    BigNat_copy(a->nat, c);
}

int BigInt_get_sign(const BigInt *a) {
    return a->sign;
}

void BigInt_negate(const BigInt *a, BigInt *c) {
    BigInt_copy(a, c);
    c->sign = -1 * c->sign;
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
    BigInt *t;

    BigInt_new(&t);
    BigInt_negate(b, t);
    BigInt_add(a, t, c);

    BigInt_destroy(t);
}

void BigInt_mul(const BigInt *a, const BigInt *b, BigInt *c) {
    BigNat_mul(a->nat, b->nat, c->nat);
    c->sign = a->sign * b->sign;
}

error_t  BigInt_div_mod_nat(const BigInt *a, const BigNat *b, BigInt *c, BigNat *r) {
    BigNat *tmp;

    if (BigNat_is_zero(b)) {
        return PE_INVALIDOPER;
    }

    BigNat_div_mod(a->nat, b, c->nat, r);
    c->sign = a->sign;

    if (c->sign < 0 && !BigNat_is_zero(r)) {
        BigNat_new(&tmp);

        BigNat_sub(b, r, tmp);
        BigNat_copy(tmp, r);
        BigNat_add_one(c->nat, c->nat);

        BigNat_destroy(tmp);
    } 

    return SUCCESS;
}

error_t BigInt_div_nat(const BigInt *a, const BigNat *b, BigInt *c) {
    error_t err;
    BigNat *rem;

    BigNat_new(&rem);

    err = BigInt_div_mod_nat(a, b, c, rem);

    BigNat_destroy(rem);
    return err;
}

error_t BigInt_mod_nat(const BigInt *a, const BigNat *b, BigNat *c) {
    error_t err;
    BigInt *tmp;
    
    BigInt_new(&tmp);

    err = BigInt_div_mod_nat(a, b, tmp, c);

    BigInt_destroy(tmp);
    return err;
}
