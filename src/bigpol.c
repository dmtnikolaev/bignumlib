#include "bigpol.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "bignumlib-error.h"
#include "bigrat.h"
#include "utils.h"

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
    const char LIST_SEP = ',';
    error_t err;
    char *str_c;
    size_t i, str_len, coeff_start, coeffs_index;

    err = SUCCESS;
    coeff_start = 0;

    str_c = strdup(str);
    if (str_c == NULL) {
        handle_critical_error(PE_ALLOC);
    }
    str_len = strlen(str_c);

    f->size = count_occurs(str_c, LIST_SEP) + 1;
    coeffs_index = f->size-1;

    BigPol_resize(f, f->size);

    for (i = 0; i < str_len+1; i++) {
        if (FAIL(err)) {
            return err;
        }

        if (str_c[i] == LIST_SEP || str_c[i] == '\0') {
            str_c[i] = '\0';

            // Если две запятые рядом, то оставляем 0.
            if (i > coeff_start) {
                err = BigRat_from_string(f->coeffs[coeffs_index], str_c + coeff_start);
            }
            coeffs_index--;
            coeff_start = i+1;
        }
    }

    while (f->size > 1 && BigNat_is_zero(f->coeffs[f->size-1]->num->nat)) {
        f->size--;
    }

    return err;
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

    for (i = f->available_size; i < new_size; i++) {
        BigRat_new(&f->coeffs[i]);
    }

    f->available_size = new_size;
}

void BigPol_to_string(const BigPol *f, char **str) {
    size_t str_len, i, shift, coeff_index;
    char **coeff_strs, **pow_strs;
    const char *sign_str;

    coeff_strs = (char **)malloc(f->size * sizeof(char *));
    pow_strs = (char **)malloc(f->size * sizeof(char *));
    if (coeff_strs == NULL || pow_strs == NULL) {
        handle_critical_error(PE_ALLOC);
    }
    
    str_len = 0;
    for (i = 0; i < f->size; i++) {
        if (BigNat_is_zero(f->coeffs[i]->num->nat)) {
            coeff_strs[i] = NULL;
            pow_strs[i] = NULL;
            continue;
        }
        
        BigRat_to_string(f->coeffs[i], &coeff_strs[i]);
        if (i != f->size-1 && f->coeffs[i]->num->sign < 0) {
            // Пропускаем минус
            coeff_strs[i][0] = ' ';
        }
        pow_strs[i] = (char *)malloc(SIZE_T_MAX_DIGITS * sizeof(char));
        sprintf(pow_strs[i], "%"SIZE_T_FORMAT_SPEC"x", i);

        // Длинна строки - сумма длин строк для каждого многочлена.
        // Строка многочлена формируется из пробела перед коэффициентом,
        // знака коэффициента, пробела после знака, коэффициента, 'x', '^',
        // степени.
        str_len += strlen(coeff_strs[i]) + strlen(pow_strs[i])
                   + 1 + 1 + 1 + 1 + 1;
    }

    shift = 0;
    // Выделяем память как минимум на 2 символа.
    str_len = str_len >= 2 ? str_len : 2;
    *str = (char *)malloc((str_len + 1) * sizeof(char));
    (*str)[0] = '\0';
    for (i = 0; i < f->size; i++) {
        coeff_index = f->size - i - 1;

        // Если коэффициент 0 - не выводим.
        if (BigNat_is_zero(f->coeffs[coeff_index]->num->nat)) {
            continue;
        }

        // Расставляем пробелы между членами.
        if (coeff_index != f->size-1) {
            strcpy(*str + shift, " ");
            shift++;
        }

        if (coeff_index != f->size-1) {
            sign_str = f->coeffs[coeff_index]->num->sign >= 0 ? "+ " : "-";
            strcpy(*str + shift, sign_str);
            shift += strlen(sign_str);
        }

        // Не выводим коэффициент, если он равен 1 или не свободный член.
        if (coeff_index != 0 &&
            f->coeffs[coeff_index]->num->nat->size == 1 &&
            f->coeffs[coeff_index]->num->nat->digits[0] == 1 &&
            f->coeffs[coeff_index]->denom->size == 1 &&
            f->coeffs[coeff_index]->denom->digits[0] == 1) {
                
            // Если был минус перед единицей, выводим пробел
            // (минус выведен выше).
            if (coeff_index != f->size-1 &&
                f->coeffs[coeff_index]->num->sign < 0) {
                strcpy(*str + shift, " ");
                shift++;
            }
            else if (coeff_index == f->size-1 &&
                f->coeffs[coeff_index]->num->sign < 0) {
                strcpy(*str + shift, "-");
                shift++;
            }
        }
        else {
            strcpy(*str + shift, coeff_strs[coeff_index]);
            shift += strlen(coeff_strs[coeff_index]);
        }

        // Не проводим дальнейшие действия, если степень - 0.
        if (coeff_index == 0) {
            continue;
        }

        strcpy(*str + shift, "x");
        shift++;

        // Не проводим дальнейшие действия, если степень - 1.
        if (coeff_index == 1) {
            continue;
        }

        strcpy(*str + shift, "^");
        shift++;
        strcpy(*str + shift, pow_strs[coeff_index]);
        shift += strlen(pow_strs[coeff_index]);
    }

    // Если исходный многочлен равен 0, то строка будет пустой.
    if (strlen(*str) == 0) {
        (*str)[0] = '0';
        (*str)[1] = '\0';
    }

    for (i = 0; i < f->size; i++) {
        free(coeff_strs[i]);
        free(pow_strs[i]);
    }
    free(coeff_strs);
    free(pow_strs);

}

void BigPol_copy(const BigPol *f, BigPol *h) {
    size_t i;
    BigPol_resize(h, f->size);
    h->size = f->size;
    for (i = 0; i < f->size; i++) {
        BigRat_copy(f->coeffs[i], h->coeffs[i]);
    }
}

void BigPol_sum(const BigPol *f, const BigPol *g, BigPol *h) {
    size_t i, h_size, com_size;

    h_size = MAX(f->size, g->size);
    com_size = f->size > g->size ? g->size : f->size;
    BigPol_resize(h, h_size);
    h->size = h_size;

    for (i = 0; i < com_size; i++) {
        BigRat_sum(f->coeffs[i], g->coeffs[i], h->coeffs[i]);
    }
    for(; i < f->size; i++) {
        BigRat_copy(f->coeffs[i], h->coeffs[i]);
    }
    for(; i < g->size; i++) {
        BigRat_copy(g->coeffs[i], h->coeffs[i]);
    }
}

void BigPol_sub(const BigPol *f, const BigPol *g, BigPol *h) {
    size_t i, h_size, com_size;

    h_size = MAX(f->size, g->size);
    com_size = f->size > g->size ? g->size : f->size;
    BigPol_resize(h, h_size);
    h->size = h_size;

    for (i = 0; i < com_size; i++) {
        BigRat_sub(f->coeffs[i], g->coeffs[i], h->coeffs[i]);
    }
    for(; i < f->size; i++) {
        BigRat_copy(f->coeffs[i], h->coeffs[i]);
    }
    for(; i < g->size; i++) {
        BigInt_negate(g->coeffs[i]->num, h->coeffs[i]->num);
    }
}

void BigPol_mul_scalar(const BigPol *f, const BigRat *c, BigPol *h) {
    size_t i;
    BigPol_resize(h, f->size);
    h->size = f->size;

    for (i = 0; i < f->size; i++) {
        BigRat_mul(c, f->coeffs[i], h->coeffs[i]);
    }
}

void BigPol_mul_expx(const BigPol *f, const size_t k, BigPol *h) {
   	size_t i;

    BigPol_resize(h, k + f->size + 1);
    h->size = k + f->size;
        
    for (i = 0; i < f->size; i++) {
        BigRat_copy(f->coeffs[i], h->coeffs[i+k]);
    }
    for (i = k - 1; i < k; i--) {
        h->coeffs[i]->num->nat->digits[0] = 0;
        h->coeffs[i]->num->nat->size = 1;
        h->coeffs[i]->num->sign = 0;
        h->coeffs[i]->denom->digits[0] = 1;
        h->coeffs[i]->denom->size = 1;
    }
}

void BigPol_get_leading(const BigPol *f, BigRat *a_n) {
    BigRat_copy(f->coeffs[f->size-1], a_n);
}

void BigPol_get_deg(const BigPol *f, size_t *deg) {
    *deg = f->size - 1;
}

void BigPol_fac(const BigPol *f, BigPol *h, BigRat *c) {
    BigNat *t, *t1;
	size_t i;
	
    BigPol_resize(h, f->size);
	BigNat_new(&t);
	BigNat_new(&t1);

	for (i = 0; i < f->size; i++) {
		BigNat_gcd(f->coeffs[i]->num->nat, t, t1);
		BigNat_copy(t1, t);
	}
	BigNat_copy(t, c->num->nat);

    c->num->sign = f->coeffs[f->size-1]->num->sign;
    
    memset(t->digits, 0, t->available_size);
    t->digits[0] = 1;
	for (i = 0; i < f->size; i++) {
		BigNat_lcm(f->coeffs[i]->denom, t, t1);
        BigNat_copy(t1, t);
	}
	BigNat_copy(t, c->denom);

    BigPol_resize(h, f->size);
    for (i = 0; i < h->size; i++) {
		BigRat_div(f->coeffs[i], c, h->coeffs[i]);
	}
	
	BigNat_destroy(t);
	BigNat_destroy(t1);
}

void BigPol_mul(const BigPol *f, const BigPol *g, BigPol *h) {
	size_t i;
    BigPol *tmp1, *tmp2;
	
    BigPol_new(&tmp1);
    BigPol_new(&tmp2);
    BigPol_resize(h, f->size + g->size);

    for (i = 0; i < f->size; i++) {
        BigPol_mul_expx(g, i, tmp1);
        BigPol_mul_scalar(tmp1, f->coeffs[i], tmp2);
        BigPol_sum(tmp2, h, tmp1);
        BigPol_copy(tmp1, h);
    }
}

void BigPol_mul_on_part(const BigPol *f, const BigPol *g, size_t i, BigPol *h) {
	BigPol *t;
	
	BigPol_new(&t);
	BigPol_resize(t, g->size);
	BigRat_copy(g->coeffs[i], t->coeffs[i]);
	BigPol_mul(f, t, h);
	BigPol_destroy(t);
}

error_t BigPol_div(const BigPol *f, const BigPol *g, BigPol *h) {
    size_t i, k, pow_d;
	BigPol *f_copy, *tmp1, *tmp2;
	
	if ((g->size == 1) && BigNat_is_zero(g->coeffs[0]->num->nat)) {
		return PE_INVALIDOPER;
	}
	
	BigPol_new(&tmp1);
    BigPol_new(&tmp2);
    BigPol_new(&f_copy);

	k = f->size - g->size + 1;
	BigPol_resize(h, k);
    BigPol_resize(tmp1, k);
    BigPol_copy(f, f_copy);

    i = k-1;
    h->size = 0;
	while (f_copy->size >= g->size) {
        h->size++;
        pow_d = f_copy->size - g->size;

        BigPol_mul_expx(g, pow_d, tmp1);
        BigRat_div(f_copy->coeffs[f_copy->size-1], tmp1->coeffs[tmp1->size-1],
                    h->coeffs[i]);

        BigPol_mul_scalar(tmp1, h->coeffs[i], tmp2);

        BigPol_sub(f_copy, tmp2, tmp1);
        BigPol_copy(tmp1, f_copy);

        f_copy->size--;
        i--;
        
	}

    BigPol_destroy(f_copy);
    BigPol_destroy(tmp1);
    BigPol_destroy(tmp2);
    return SUCCESS;
}

error_t BigPol_mod(const BigPol *f, const BigPol *g, BigPol *h) {
    BigPol *q, *pq;
	
    if ((g->size == 1) && BigNat_is_zero(g->coeffs[0]->num->nat)) {
		return PE_INVALIDOPER;
	}

	BigPol_new(&q);
	BigPol_new(&pq);
	BigPol_div(f, g, q);
	BigPol_mul(g, q, pq);
	BigPol_sub(f, pq, h);
	
    while (h->size > 1 && BigNat_is_zero(h->coeffs[h->size-1]->num->nat)) {
        h->size--;
    }

	BigPol_destroy(q);
	BigPol_destroy(pq);

    return SUCCESS;
    }

error_t BigPol_gcd(const BigPol *f, const BigPol *g, BigPol *h) {
    BigPol *t, *f_copy, *g_copy;
    BigRat *c;

    BigRat_new(&c);
    BigPol_new(&t);
    BigPol_new(&f_copy);
    BigPol_new(&g_copy);
    BigPol_copy(f, f_copy);
    BigPol_copy(g, g_copy);

    while (!((g_copy->size == 1) && BigNat_is_zero(g_copy->coeffs[0]->num->nat)) &&
           !((f_copy->size == 1) && BigNat_is_zero(f_copy->coeffs[0]->num->nat))) {
        if (f_copy->size > g_copy->size) {
            BigPol_mod(f_copy, g_copy, t);
            BigPol_copy(t, f_copy);
        }
        else {
            BigPol_mod(g_copy, f_copy, t);
            BigPol_copy(t, g_copy);
        }
    }
    if (((g_copy->size == 1) && BigNat_is_zero(g_copy->coeffs[0]->num->nat))) {
        BigPol_copy(f_copy, h);
    }
    else {
        BigPol_copy(g_copy, h);
    }
    
    BigPol_copy(h, t);
    BigPol_fac(t, h, c);

    BigRat_destroy(c);
    BigPol_destroy(t);
    BigPol_destroy(f_copy);
    BigPol_destroy(g_copy);
    return SUCCESS;
}

void BigPol_der(const BigPol *f, BigPol *h) {
    BigRat *coeff_d;
    size_t i;

    if (f->size == 1) {
        BigRat_destroy(h->coeffs[0]);
        BigRat_new(&h->coeffs[0]);
        h->size = 1;
    }

    BigRat_new(&coeff_d);
    BigPol_resize(h, f->size-1);
    h->size = f->size-1;

    for (i = 0; i < f->size-1; i++) {
        BigRat_from_num(coeff_d, i+1);
        char *s;
        BigRat_to_string(coeff_d, &s);
        BigRat_mul(f->coeffs[i+1], coeff_d, h->coeffs[i]);
    }
}

void BigPol_nmr(const BigPol *f, BigPol *h) {
    BigPol *der, *gcd;

    BigPol_new(&der);
    BigPol_new(&gcd);

    BigPol_der(f, der);
    BigPol_gcd(f, der, gcd);
    BigPol_div(f, gcd, h);

    BigPol_destroy(der);
    BigPol_destroy(gcd);
}

