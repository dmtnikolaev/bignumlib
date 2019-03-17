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
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_new(BigInt **a);

/**
 * Очищает память, выделенную под число.
 * 
 * @param a Число
 * 
 * @author
 */
void BigInt_destroy(BigNat *a);

/**
 * Преобразует натуральное число в целое.
 * 
 * @note По умолчанию натуральное число преобразуем в целое положительное.
 *  
 * @param a Целое число.
 * @param b Натуральное число.
 * 
 * @author
 */
void BigInt_from_nat(BigInt *a, BigNat *b);

/**
 * Преобразует целое неотрицательное число в натуральное.
 * 
 * @param a Целое число.
 * @param c Натуральное число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_to_nat(BigInt *a, BigNat *c);

/**
 * Преобразует строку в число.
 * 
 * @param a Число.
 * @param str Строка.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_from_string(BigInt *a, char *str);

/**
 * Преобразует число в строку.
 * 
 * @param a Число.
 * @param string Строка.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_to_string(BigInt *a, char **string);

/**
 * Возвращает абсолютное значение числа.
 * 
 * @param a Число.
 * @param c Абсолютное значение числа.
 * 
 * @author
 */
void BigInt_abs(BigInt *a, BigNat *c);

/**
 * Возвращает знак числа.
 * 
 * @param a Число.
 * @return int Знак числа.
 * 
 * @author
 */
int BigInt_get_sign(BigInt *a);

/**
 * Умножает число на -1.
 * 
 * @param a Число.
 * @param b Противоположное число.
 * 
 * @author
 */
void BigInt_negate(BigInt *a, BigInt *b);

/**
 * Складывает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Сумма.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_add(BigInt *a, BigInt *b, BigInt *c);

/**
 * Вычитает из первого числа второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Разность.
 * @return errno_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_sub(BigInt *a, BigInt *b, BigInt *c);

/**
 * Умножает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Произведение.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_mul(BigInt *a, BigInt *b, BigInt *c);

/**
 * Делит целое число на натуральное с остатком.
 * 
 * @param a Целое число.
 * @param b Натуральное число.
 * @param c Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_div_nat(BigInt *a, BigNat *b, BigInt *c);

/**
 * Находит остаток от деления целого числа на натуральное.
 * 
 * @param a Целое число.
 * @param b Натуральное число.
 * @param c Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigInt_mod_nat(BigInt *a, BigNat *b, BigNat *c);

#endif /* !BIGINT_H */
