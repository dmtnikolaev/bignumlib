//
// @author Stepan Repin.
//

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
 */
void BigRat_new(BigRat **a);

/**
 * Очищает память, выделенную под число.
 * 
 * @param a Число
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
 */
error_t BigRat_from_int(BigRat *a, const BigInt *integ);

/**
 * Преобразует рациональное число в целое.
 * 
 * @param a Рациональное число.
 * @param integ Целое число, равное рациональному.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigRat_to_int(const BigRat *a, BigInt *integ);

/**
 * Преобразует строку в число.
 * 
 * @param a Число.
 * @param str Строка.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigRat_from_string(BigRat *a, const char *str);

/**
 * Преобразует число в строку.
 * 
 * @param a Число.
 * @param str Строка.
 */
void BigRat_to_string(const BigRat *a, char **str);

/**
 * Переводит число в дробь.
 * 
 * @param a Дробь.
 * @param i Число.
 */
void BigRat_from_num(BigRat *a, size_t i);

/**
 * Сокращает дробь.
 * 
 * @param a Дробь.
 * @param c Несократимая дробь, равная a.
 */
void BigRat_reduce(const BigRat *a, BigRat *c);

/**
 * Проверяет, является ли число целым (знаменатель равен 1).
 * 
 * @param a Число.
 */
int BigRat_is_int(const BigRat *a);

/**
 * Складывает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Сумма.
 */
void BigRat_sum(const BigRat *a, const BigRat *b, BigRat *c);

/**
 * Приводит дробь к данному знаменателю.
 * 
 * @param a Исходная дробь.
 * @param denom Знаменатель.
 * @param c Дробь со знаменателем denom, равная исходной.
 */
void BigRat_to_denom(const BigRat *a, const BigNat *denom, BigRat *c);

/**
 * Вычитает из первого числа второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Разность.
 */
void BigRat_sub(const BigRat *a, const BigRat *b, BigRat *c);

/**
 * Умножает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Произведение.
 */
void BigRat_mul(const BigRat *a, const BigRat *b, BigRat *c);

/**
 * Делит первое число на второе.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigRat_div(const BigRat *a, const BigRat *b, BigRat *c);

#endif /* !BIGRAT_H */
