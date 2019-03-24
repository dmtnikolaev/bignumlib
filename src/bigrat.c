#include "bigrat.h"

#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "bignat.h"
#include "bignumlib-error.h"

void BigRat_new(BigRat **a) {
    *a = (BigRat *)malloc(sizeof(BigRat));
    if (*a == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    BigInt_new(&(*a)->num);
    BigNat_new(&(*a)->denom);
}

void BigRat_destroy(BigRat *a) {
    if (a == NULL) {
        return;
    }

    BigInt_destroy(a->num);
    BigNat_destroy(a->denom);
}

void BigRat_copy(const BigRat *a, BigRat *copy) {
    BigInt_copy(a->num, copy->num);
    BigNat_copy(a->denom, copy->denom);
}

error_t BigRat_from_int(BigRat *a, const BigInt *integ) {
    BigInt_copy(integ, a->num);
    
    if (a->denom->size != 1) {
        return IE_INVALIDPARAM;
    }

    a->denom->digits[0] = 1;

    return SUCCESS;
}

error_t BigRat_to_int(const BigRat *a, BigInt *integ) {
    if (BigRat_is_int(a)) {
        BigInt_copy(a->num, integ);
        return SUCCESS;
    }
    return IE_INVALIDPARAM;
}

error_t BigRat_from_string(BigRat *a, const char *str) {
    error_t err;
    char *str_copy, *tok_p;

    str_copy = strdup(str);
    if (str_copy == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    tok_p = strtok(str_copy, "/");
    if (tok_p == NULL) {
        free(str_copy);
        return PE_PARSING;
    }

    err = BigInt_from_string(a->num, tok_p);
    if (FAIL(err)) {
        free(str_copy);
        return err;
    }

    tok_p = strtok(NULL, "/");
    if (tok_p == NULL) {
        free(str_copy);
        return PE_PARSING;
    }

    err = BigNat_from_string(a->denom, tok_p);
    if (FAIL(err)) {
        free(str_copy);
        return err;
    }

    tok_p = strtok(str_copy, "/");
    free(str_copy);
    if (tok_p != NULL) {
        return PE_PARSING;
    }

    return SUCCESS;
}

void BigRat_to_string(const BigRat *a, char **str) {
    char *num_str, *denom_str;
    size_t num_str_len, denom_str_len;

    *str = NULL;

    BigInt_to_string(a->num, &num_str);
    num_str_len = strlen(num_str);

    BigNat_to_string(a->denom, &denom_str);
    denom_str_len = strlen(denom_str);

    *str =(char *)
        malloc((num_str_len + denom_str_len + 1 + 1) * sizeof(char));
    if (str == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    strcpy(*str, num_str);
    strcpy(*str + num_str_len, "/");
    strcpy(*str + num_str_len + 1, denom_str);
}

void BigRat_reduce(const BigRat *a, BigRat *b) {
    BigNat *gcd;

    BigNat_new(&gcd);
    BigNat_gcf(a->num->nat, b->denom, gcd);

    b->num->sign = a->num->sign;

    BigNat_div(a->num->nat, gcd, b->num->nat);
    BigNat_div(a->denom, gcd, b->denom);
    BigNat_destroy(gcd);
}

int BigRat_is_int(const BigRat *a) {
    return a->denom->size == 1 && a->denom->digits[0] == 1;
}

void BigRat_sum(const BigRat *a, const BigRat *b, BigRat *c) {
    BigRat *t, *temp_a, *temp_b;

    BigRat_new(&t);
    BigRat_new(&temp_a);
    BigRat_new(&temp_b);

    BigNat_lcm(a->denom, b->denom, t->denom);

    BigRat_to_denom(a, t->denom, temp_a);
    BigRat_to_denom(b, t->denom, temp_b);
    BigInt_add(temp_a->num, temp_b->num, t->num);

    BigRat_destroy(temp_a);
    BigRat_destroy(temp_b);

    BigRat_reduce(t, c);

    BigRat_destroy(t);
}

void BigRat_to_denom(const BigRat *a, const BigNat *denom, BigRat *c) {
    BigNat *d_a_num;

    BigNat_copy(denom, c->denom);

    BigNat_new(&d_a_num);
    BigNat_div(denom, a->denom, d_a_num);
    BigNat_mul(a->num->nat, d_a_num, c->num->nat);
    c->num->sign = a->num->sign;
    BigNat_destroy(d_a_num);
}

void BigRat_sub(const BigRat *a, const BigRat *b, BigRat *c) {
    BigRat *t;
    BigRat_new(&t);
    BigInt_negate(b->num, t->num);
    BigNat_copy(b->denom, t->denom);
    BigRat_sum(a, t, c);
}

void BigRat_mul(const BigRat *a, const BigRat *b, BigRat *c) {
    BigRat *t;

    BigRat_new(&t);

    BigInt_mul(a->num, b->num, t->num);
    BigNat_mul(a->denom, b->denom, t->denom);
    BigRat_reduce(t, c);

    BigRat_destroy(t);
}

error_t BigRat_div(const BigRat *a, const BigRat *b, BigRat *c) {
    BigRat *t;
    
    if (BigNat_is_zero(b->num->nat)) {
        return IE_INVALIDPARAM;
    }

    BigRat_new(&t);

    BigNat_mul(a->num->nat, b->denom, t->num->nat);
    BigNat_mul(a->denom, b->num->nat, t->denom);
    t->num->sign = a->num->sign * b->num->sign;
    BigRat_reduce(t, c);

    BigRat_destroy(t);

    return SUCCESS;
}
