#ifndef BIGRAT_H
#define BIGRAT_H

#include "bigint.h"
#include "bignat.h"
#include "bignumlib-error.h"

/**
 * Представляет длинное рациональное число.
 */
typedef struct {
    /**
     * Числитель дроби.
     */
    BigInt *num;

    /**
     * Знаменатель дроби.
     */
    BigNat *denom;
} BigRat;

/**
 * Создает новое рациональное число, равное 0/1.
 * 
 * @param a Новое число.
 * 
 * @author
 */
void BigRat_new(BigRat **a);

/**
 * Очищает память, выделенную под число.
 * 
 * @param a Число
 * 
 * @author
 */
void BigRat_destroy(BigRat *a);

/**
 * Копирует число.
 * 
 * @param a Число.
 * @param copy Копия числа.
 */
void BigRat_copy(const BigRat *a, BigRat *copy);

/**
 * Преобразует целое число в рациональное.
 * 
 * @param a Рациональное число
 * @param integ Целое число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigRat_from_int(BigRat *a, const BigInt *integ);

/**
 * Преобразует рациональное число в целое.
 * 
 * @param a Рациональное число.
 * @param integ Целое число, равное рациональному.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigRat_to_int(const BigRat *a, BigInt *integ);

/**
 * Преобразует строку в число.
 * 
 * @param a Число.
 * @param str Строка.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigRat_from_string(BigRat *a, const char *str);

/**
 * Преобразует число в строку.
 * 
 * @param a Число.
 * @param str Строка.
 * 
 * @author
 */
void BigRat_to_string(const BigRat *a, char **str);

/**
 * Сокращает дробь.
 * 
 * @param a Дробь.
 * 
 * @author
 */
void BigRat_reduce(BigRat *a);

/**
 * Проверяет, является ли число целым (знаменатель равен 1).
 * 
 * @param a Число.
 * 
 * @author
 */
int BigRat_is_int(const BigRat *a);

/**
 * Складывает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Сумма.
 * 
 * @author
 */
void BigRat_sum(const BigRat *a, const BigRat *b, BigRat *c);

/**
 * Вычитает из первого числа второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Разность.
 * 
 * @author
 */
void BigRat_sub(const BigRat *a, const BigRat *b, BigRat *c);

/**
 * Умножает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Произведение.
 * 
 * @author
 */
void BigRat_mul(const BigRat *a, const BigRat *b, BigRat *c);

/**
 * Делит первое число на второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigRat_div(const BigRat *a, const BigRat *b, BigRat *c);

#endif /* !BIGRAT_H */
