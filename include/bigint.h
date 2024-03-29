//
// @author Polina Maltseva.
//

#ifndef BIGINT_H
#define BIGINT_H

#include "bignat.h"
#include "bignumlib-error.h"

/**
 * Представляет длинное целое число.
 */
typedef struct {
    /**
     * Натуральное представление числа.
     */
    BigNat *nat;

    /**
     * Знак числа.
     * 
     * @note sign = 1 - число положительное, 
     *              0 - равное нулю, 
     *             -1 - отрицательное.
     */
    int sign;
} BigInt;

/**
 * Создает новое число, равное 0.
 * 
 * @param a Новое число.
 */
void BigInt_new(BigInt **a);

/**
 * Очищает память, выделенную под число.
 * 
 * @param a Число.
 */
void BigInt_destroy(BigInt *a);

/**
 * Копирует число.
 * 
 * @param a Число.
 * @param copy Копия числа.
 */
void BigInt_copy(const BigInt *a, BigInt *copy);

/**
 * Преобразует натуральное число в целое.
 *  
 * @param a Целое число.
 * @param b Натуральное число.
 */
void BigInt_from_nat(BigInt *a, const BigNat *b);

/**
 * Преобразует целое неотрицательное число в натуральное.
 * 
 * @param a Целое число.
 * @param c Натуральное число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigInt_to_nat(const BigInt *a, BigNat *c);

/**
 * Преобразует строку в число.
 * 
 * @param a Число.
 * @param str Строка.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigInt_from_string(BigInt *a, const char *str);

/**
 * Преобразует число в строку.
 * 
 * @param a Число.
 * @param string Строка.
 */
void BigInt_to_string(const BigInt *a, char **string);

/**
 * Возвращает абсолютное значение числа.
 * 
 * @param a Число.
 * @param c Абсолютное значение числа.
 */
void BigInt_abs(const BigInt *a, BigNat *c);

/**
 * Возвращает знак числа.
 * 
 * @param a Число.
 * @return int Знак числа.
 */
int BigInt_get_sign(const BigInt *a);

/**
 * Умножает число на -1.
 * 
 * @param a Число.
 * @param c Противоположное число.
 */
void BigInt_negate(const BigInt *a, BigInt *c);

/**
 * Складывает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Сумма.
 */
void BigInt_add(const BigInt *a, const BigInt *b, BigInt *c);

/**
 * Вычитает из первого числа второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Разность.
 */
void BigInt_sub(const BigInt *a, const BigInt *b, BigInt *c);

/**
 * Умножает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Произведение.
 */
void BigInt_mul(const BigInt *a, const BigInt *b, BigInt *c);

/**
 * Делит целое число на натуральное с остатком.
 * 
 * @param a Целое число.
 * @param b Натуральное число.
 * @param c Частное.
 * @param r Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t  BigInt_div_mod_nat(const BigInt *a, const BigNat *b, BigInt *c,
                            BigNat *r);

/**
 * Делит целое число на натуральное с остатком.
 * 
 * @param a Целое число.
 * @param b Натуральное число.
 * @param c Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigInt_div_nat(const BigInt *a, const BigNat *b, BigInt *c);

/**
 * Находит остаток от деления целого числа на натуральное.
 * 
 * @param a Целое число.
 * @param b Натуральное число.
 * @param c Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigInt_mod_nat(const BigInt *a, const BigNat *b, BigNat *c);

#endif /* !BIGINT_H */
