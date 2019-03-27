//
// @author Egor Tuliandin.
//

#ifndef BIGNAT_H
#define BIGNAT_H

#include <stddef.h>
#include "bignumlib-error.h"

/**
 * Цифра - десятичное число из промежутка [0, 9].
 */
typedef unsigned char digit;

/**
 * Представляет длинное натуральное число.
 */
typedef struct {
    /**
     * Цифры числа.
     */
    digit *digits;

    /**
     * Количество разрядов в числе (не учитывая нули в конце - неиспользуемые разряды).
     */
    size_t size;

    /**
     * Количество разрядов, для которых уже выделена память.
     */
    size_t available_size;
} BigNat;

/**
 * Создает новое число, равное 0.
 * 
 * @param a Новое число.
 */
void BigNat_new(BigNat **a);

/**
 * Очищает память, выделенную под число.
 * 
 * @param a Число.
 */
void BigNat_destroy(BigNat *a);

/**
 * Увеличивает число разрядов в числе. Если new_size <= a->size, то ничего
 * не делать.
 * 
 * @param a Число.
 * @param new_size Новый размер.
 */
void BigNat_resize(BigNat *a, size_t new_size);

/**
 * Копирует число.
 * 
 * @param a Число.
 * @param copy Копия числа.
 */
void BigNat_copy(const BigNat *a, BigNat *copy);

/**
 * Создает новое число на основе его строкого представления.
 * 
 * @param a Новое число.
 * @param str Строка, содержащая число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_from_string(BigNat *a, const char *str);

/**
 * Преобразует число в строку.
 * 
 * @param a Число.
 * @param result Строковое представление числа.
 */
void BigNat_to_string(const BigNat *a, char **result);

/**
 * Сравнивает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @return int Возвращает положительное число, если первое
 *             больше второго; 0, если числа равны; иначе
 *             отрицательное число.
 */
int BigNat_compare(const BigNat *a, const BigNat *b);

/**
 * Проверяет, равно ли число 0.
 * 
 * @param a Число.
 * @return int Положительное число, если равно 0. Иначе 0.
 */
int BigNat_is_zero(const BigNat *a);

/**
 * Добавляет к числу 1.
 * 
 * @param a Число.
 * @param c Результат сложения.
 */
void BigNat_add_one(const BigNat *a, BigNat *c);

/**
 * Складывает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Сумма.
 */
void BigNat_sum(const BigNat *a, const  BigNat *b, BigNat *c);

/**
 * Вычитает из первого числа второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Разность.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_sub(const BigNat *a, const  BigNat *b, BigNat *c);

/**
 * Умножает число на цифру (число в промежутке [0, 9]).
 * 
 * @param a Число.
 * @param d Цифра.
 * @param c Результат.
 */
void BigNat_mul_by_digit(const BigNat *a, digit d, BigNat *c);

/**
 * Умножает число на степень 10 (10^k).
 * 
 * @param a Число.
 * @param k Степень 10.
 * @param c Результат.
 */
void BigNat_mul_by_exp10(const BigNat *a, int k, BigNat *c);

/**
 * Умножает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Произведение.
 */
void BigNat_mul(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Вычитает из первого числа второе, умноженное на цифру.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param d Цифра.
 * @param c Результат.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_sub_proportional(const BigNat *a, const BigNat *b, digit d,
                                BigNat *c);

/**
 * Вычисляет первую цифру деления первого числа на второе, домноженное на
 * 10^k,где k - номер позиции этой цифры (номер считается с нуля).
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param d Результат.
 * @param k Количество цифр, на которые сдвигается второе число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_div_first_digit(const BigNat *a, const BigNat *b,
                                 digit *d, size_t *k);

/**
 * Делит первое число на второе, возвращает частное и остаток.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Частное.
 * @param r Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_div_mod(const BigNat *a, const BigNat *b, BigNat *c, BigNat *r);

/**
 * Делит первое число на второе, возвращает частное/
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_div(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Делит первое число на второе и возвращает остаток.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigNat_mod(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Находит НОД двух чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c НОД.
 */
void BigNat_gcd(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Находит НОК двух чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c НОК.
 */
void BigNat_lcm(const BigNat *a, const BigNat *b, BigNat *c);

#endif /* !BIGNAT_H */
