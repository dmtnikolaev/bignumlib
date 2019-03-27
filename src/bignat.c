#include "bignat.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "bignumlib-error.h"
#include "utils.h"

void BigNat_new(BigNat **a) {
    *a = (BigNat *)malloc(sizeof(BigNat));
    if (*a == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    // Выделяем память только под одну цифру - 0.
    (*a)->size = 1;
    (*a)->digits = (digit *)malloc((*a)->size * sizeof(digit));
    if ((*a)->digits == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    (*a)->digits[0] = 0;
    (*a)->available_size = (*a)->size;
}

void BigNat_destroy(BigNat *a) {
    if (a != NULL) {
        free(a->digits);
        a->available_size = 0;
        a->size = 0;
    }
    free(a);
}

void BigNat_resize(BigNat *a, size_t new_size) {
    if (new_size <= a->available_size) {
        return;
    }

    a->digits = (digit *)realloc(a->digits, new_size);
    if (a->digits == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    // Обнуляем только что добавленные разряды.
    memset(a->digits + a->available_size, 0,
        (new_size - a->available_size) * sizeof(digit));
    a->available_size = new_size;
}

void BigNat_copy(const BigNat *a, BigNat *copy) {
    BigNat_resize(copy, a->size);
    memcpy(copy->digits, a->digits, a->size * sizeof(digit));
    copy->size = a->size;
}

error_t BigNat_from_string(BigNat *a, const char *str) {
    size_t i, str_len, a_size, num_start;
    error_t err;

    // Убираем пробелы в начале и в конце строки.
    str_len = strlen(str);
    while (isspace(str[str_len-1])) {
        str_len--;
    }
    
    num_start = 0;
    while (isspace(str[num_start])) {
        num_start++;
    }

    if (str_len == 0) {
        return PE_PARSING;
    }

    a_size = str_len - num_start;
    BigNat_resize(a, a_size);
    a->size = 0;

    // По-символьно переводим строку в число.
    for (i = num_start; i < str_len ; i++) {
        err = char_to_digit(str[str_len - i - 1 + num_start], &a->digits[a->size++]);
        if (FAIL(err)) {
            return err;
        }
    }

    // Убираем из числа лидирующие нули.
    while (a->digits[a->size-1] == 0 && a->size-1 > 0) {
        a->size--;
    }

    return SUCCESS;
}

void BigNat_to_string(const BigNat *a, char **result) {
    size_t i;

    *result = (char *)malloc((a->size + 1) * sizeof(char));
    if (*result == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    for (i = 0; i < a->size; i++) {
        (*result)[i] = digit_to_char(a->digits[a->size - i - 1]);
    }
    (*result)[i] = '\0';
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
        for (i = a->size-1; i < a->size; i--) {
            if (a->digits[i] == b->digits[i]) {
                continue;
            }

            return a->digits[i] > b->digits[i] ? 1 : -1;
        }
        return 0;
    }
}

int BigNat_is_zero(const BigNat *a) {
    size_t i;

    for (i = a->size-1; i < a->size; i--) {
        if (a->digits[i] != 0) {
                return 0;
        }
    }
    return 1;
}

void BigNat_add_one(const BigNat *a, BigNat *c) {
    size_t i;
    digit c_temp = 1;

    BigNat_resize(c, a->size + 1);
    BigNat_copy(a, c);

    for (i = 0; i < a->size; i++) {
        c->digits[i] = c_temp + a->digits[i];
        c_temp = 0;
        if (c->digits[i] < 10) {
            break;
        }
        else {
            c_temp = 1;
            c->digits[i] = 0;
        }
    }
    
    if (c_temp == 1) {
        c->size = a->size + 1;
        c->digits[i] = 1;
    }
    else {
        c->size = a->size;
    }
}


void BigNat_sum(const BigNat *a,const  BigNat *b, BigNat *c) {
    digit a_d, b_d, c_d_carry;
    size_t i, max_size;

    max_size = MAX(a->size, b->size);
    BigNat_resize(c, max_size+1);

    c_d_carry = 0;
    for (i = 0; i < max_size; i++) {
        a_d = i >= a->size ? 0 : a->digits[i];
        b_d = i >= b->size ? 0 : b->digits[i];

        c_d_carry += a_d + b_d;
        c->digits[i] = c_d_carry % 10;
        c_d_carry /= 10;
    }

    if (c_d_carry > 0) {
        c->digits[i] = c_d_carry;
        i++;
    }

    c->size = i;
}

error_t BigNat_sub(const BigNat *a, const  BigNat *b, BigNat *c) {
    size_t i;
    digit loan, b_d;

    loan = 0;
    BigNat_copy(a, c);
    c->size = 0;

    for (i = 0; i < a->size; i++) {
        b_d = i < b->size ? b->digits[i] : 0;
        if (c->digits[i] - loan < b_d) {
            c->digits[i] += 10 - b_d - loan; 
            loan = 1;
        }
        else {
            c->digits[i] -= b_d + loan;
            loan = 0;
        }
        c->size++;
    }

    // Убираем из числа лидирующие нули.
    while (c->digits[c->size-1] == 0 && c->size-1 > 0) {
        c->size--;
    }

    return loan == 0 ? SUCCESS : PE_INVALIDOPER;
}

void BigNat_mul_by_digit(const BigNat *a, digit d, BigNat *c) {
    size_t i;
    digit c_temp = 0;
    if (d == 0) {
        c->size = 1;
        c->digits[0] = 0;
    }
    else {
        BigNat_resize(c, a->size+1);
        for (i = 0; i < a->size; i++) {
            c->digits[i] = c_temp + (a->digits[i] * d);
            c_temp = c->digits[i] / 10;
            c->digits[i] %= 10;
        }
        c->size = i;
        if (c_temp != 0) {
            c->size += 1;
            c->digits[i] = c_temp;
        }
    }
}

void BigNat_mul_by_exp10(const BigNat *a, int k, BigNat *c) {
    size_t i;

    if (BigNat_is_zero(a)) {
        BigNat_copy(a, c);
        return;
    }

    BigNat_resize(c, a->size + k);
    c->size = a->size + k;
    for (i = c->size - 1; i >= k && i < c->size; i--) {
        c->digits[i] = a->digits[i-k];
    }
    for (i = 0; i < k; i++) {
        c->digits[i] = 0;
    }
}

//
// Реализовано обыкновенное умножение столбиком.
//
void BigNat_mul(const BigNat *a, const BigNat *b, BigNat *c) {
    size_t i;
    BigNat *tmp_mul;
    BigNat *tmp_shifted;
    BigNat *tmp_c;

    BigNat_new(&tmp_mul);
    BigNat_new(&tmp_shifted);
    BigNat_new(&tmp_c);

    BigNat_resize(c, a->size + b->size);
    
    for (i = 0; i < b->size; i++) {
        BigNat_mul_by_digit(a, b->digits[i], tmp_mul);
        BigNat_mul_by_exp10(tmp_mul, i, tmp_shifted);
        BigNat_sum(tmp_shifted, tmp_c, c);
        BigNat_copy(c, tmp_c);
    }

    c->size = a->size + b->size;
    while (c->digits[c->size-1] == 0 && c->size > 1) {
        c->size--;
    }

    BigNat_destroy(tmp_shifted);
    BigNat_destroy(tmp_c);
    BigNat_destroy(tmp_mul);
}

error_t BigNat_sub_proportional(const BigNat *a, const BigNat *b, digit d,
                                BigNat *c) {
    int comp;
    BigNat *mul_b;

    BigNat_new(&mul_b);
    BigNat_resize(c, a->size);
    BigNat_mul_by_digit(b, d, mul_b);

    comp = BigNat_compare(a, mul_b);
    if (comp > 0) {
        BigNat_sub(a, mul_b, c);
    }
    else if (comp == 0){
            c->size = 1;
            c->digits[0] = 0;
    }
    else {
        return PE_INVALIDOPER;
    }

    BigNat_destroy(mul_b);

    return SUCCESS;
}

error_t BigNat_div_first_digit(const BigNat *a, const BigNat *b,
                                 digit *d, size_t *k) {
    int comp;
    BigNat *tmp, *tmp_b_delta;
    size_t i;

    if (BigNat_is_zero(b)) {
        return PE_INVALIDOPER;
    }

    comp = BigNat_compare(a, b);
    if (comp < 0) {
        *d = 0;
    }
    else if (comp == 0){
        *d = 1;
    }
    else {
        BigNat_new(&tmp);
        BigNat_resize(tmp, a->size);

        // Выбираем из числа подчисло tmp (слева на право), которое при делении
        // на b дает цифру [1..9].
        tmp->size = b->size-1;
        while (BigNat_compare(tmp, b) < 0) {
            tmp->size++;
            for (i = 0; i < tmp->size; i++) {
                tmp->digits[tmp->size - i - 1] = a->digits[a->size - i - 1];
            }
        }

        BigNat_new(&tmp_b_delta);

        // Делим число tmp на b.
        *d = 0;
        do {
            BigNat_sub(tmp, b, tmp_b_delta);
            BigNat_copy(tmp_b_delta, tmp);
            (*d)++;
        }
        while (BigNat_compare(tmp, b) >= 0);

        *k = a->size - i;

        BigNat_destroy(tmp);
        BigNat_destroy(tmp_b_delta);
    }
    return SUCCESS;
}

//
// Реализуем обыкновенное деление двух чисел школьным способом через столбик.
//
error_t BigNat_div_mod(const BigNat *a, const BigNat *b, BigNat *c, BigNat *rem) {
    size_t d_k;
    BigNat *tmp, *shifted_b;
    digit d;

    if (BigNat_is_zero(b)) {
        return PE_INVALIDOPER;
    }

    if (BigNat_compare(a, b) < 0) {
        c->size = 1;
        c->digits[0] = 0;
        BigNat_copy(a, rem);
    }
    else if (BigNat_compare(a, b) == 0) {
        c->size = 1;
        c->digits[0] = 1;
    }
    else {
        BigNat_resize(c, a->size);
        BigNat_new(&tmp);
        BigNat_new(&shifted_b);

        BigNat_copy(a, rem);

        c->size = 0;
        while (BigNat_compare(rem, b) >= 0) {
            BigNat_div_first_digit(rem, b, &d, &d_k);

            c->digits[d_k] = d;
            c->size = MAX(d_k + 1, c->size);

            BigNat_mul_by_exp10(b, d_k, shifted_b);
            BigNat_sub_proportional(rem, shifted_b, d, tmp);
            BigNat_copy(tmp, rem);
        }

        BigNat_destroy(tmp);
        BigNat_destroy(shifted_b);
    }
    return SUCCESS;
}

error_t BigNat_div(const BigNat *a, const BigNat *b, BigNat *c) {
    error_t err;
    BigNat *t;
    BigNat_new(&t);
    err = BigNat_div_mod(a, b, c, t);
    return err;
}

error_t BigNat_mod(const BigNat *a, const BigNat *b, BigNat *c) {
    error_t err;
    BigNat *t;
    BigNat_new(&t);
    err = BigNat_div_mod(a, b, t, c);
    return err;
}

//
// Для вычисления НОД используем алгоритм Евклида.
//
void BigNat_gcd(const BigNat *a, const BigNat *b, BigNat *c) {
    int comp;
    BigNat *mock_div, *tmp_a, *rem;

    comp = BigNat_compare(a, b);
    if (comp == 0) {
        BigNat_copy(a, c);
        return;
    }

    BigNat_new(&mock_div);
    BigNat_new(&tmp_a);
    BigNat_new(&rem);
    if (comp > 0) {
        BigNat_copy(a, tmp_a);
        BigNat_copy(b, c);
    }
    else { // comp < 0
        BigNat_copy(a, c);
        BigNat_copy(b, tmp_a);
    }


    if (!BigNat_is_zero(a) && !BigNat_is_zero(b)) {
        do {
            BigNat_div_mod(tmp_a, c, mock_div, rem);
            BigNat_copy(c, tmp_a);
            BigNat_copy(rem, c);
        }
        while (!BigNat_is_zero(rem));
    }

    BigNat_copy(tmp_a, c);

    BigNat_destroy(mock_div);
    BigNat_destroy(tmp_a);
    BigNat_destroy(rem);
}

//
// Считаем НОК по формуле (a*b)/НОД(a,b)).
//
void BigNat_lcm(const BigNat *a, const BigNat *b, BigNat *c) {
    BigNat *a_b_mul, *gcd;
    
    BigNat_new(&a_b_mul);
    BigNat_new(&gcd);

    BigNat_mul(a, b, a_b_mul);
    BigNat_gcd(a, b, gcd);
    BigNat_div(a_b_mul, gcd, c);

    BigNat_destroy(a_b_mul);
    BigNat_destroy(gcd);
}

