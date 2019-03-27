#ifndef BIGNAT_H
#define BIGNAT_H

#include <stddef.h>
#include "bignumlib-error.h"

/**
 * @file
 * Файл содержит описания функций и структур для работы с длинными
 * натуральными числами. Реализация в файле src/bignat.c.
 * 
 * @note
 * Алгоритмы, использующиеся здесь в большинстве своем довольно простые
 * (наверное). Они легко гуглятся, и что-то есть на Википедии.
 * 
 * Если возникнут вопросы, а они точно возникнут, спрашивайте в беседе.
 * 
 * На данный момент, описанные здесь функции только прикинуты и имеются лишь
 * в голове архитектора, потому вероятно какие-то из них не нужны или наоборот -
 * каких-то функций не хватает; может быть некоторые функции имеют
 * неправильные параметры, возможно есть опечатки.
 * 
 * Замечания по разработке:
 * -    Не забывайте делать все необходимые проверки (на null, на error_t
 *      вызванной функции).
 * -    Не забывайте вовремя выделять и очищать память (через *_new и
 *      *_destroy методы).
 * -    Проверяйте крайние случае.
 * -    Добавьте свое имя в 'author' для каждого метода.
 */

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
     * 
     * @note size_t - максимальный размер теоретически возможного массива
     *       любого типа.
     */
    size_t size;

    /**
     * Количество разрядов, для которых уже выделена память.
     * 
     */
    size_t available_size;
} BigNat;

/**
 * Создает новое число, равное 0.
 * 
 * @param a Новое число.
 * 
 * @author
 */
void BigNat_new(BigNat **a);

/**
 * Очищает память, выделенную под число.
 * 
 * @note Не забудьте обнулить a->size.
 * 
 * @param a Число.
 * 
 * @author
 */
void BigNat_destroy(BigNat *a);

/**
 * Увеличивает число разрядов в числе. Если new_size <= a->size, то ничего
 * не делать.
 * 
 * @param a Число.
 * @param new_size Новый размер.
 * 
 * @author
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
* Проверяет является ли это число корректным.
* 
* @note Проверяйте на NULL и a->size. Используйте эту функцию в других, для
* проверки параметров.
* 
* @param a Число.
* @return int Возвращает число, если число корректное; иначе - 0.
* 
* @author
*/
int BigNat_is_number(const BigNat *a);

/**
 * Создает новое число на основе его строкого представления.
 * 
 * @param a Новое число.
 * @param str Строка, содержащая число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigNat_from_string(BigNat *a, const char *str);

/**
 * Преобразует число в строку.
 * 
 * @param a Число.
 * @param result Строковое представление числа.
 * 
 * @author
 */
void BigNat_to_string(const BigNat *a, char **result);

/**
 * Возвращает константу 0.
 * 
 * @note Реализуется через ключевое слово 'static'.
 * 
 * @param zero Полученная константа.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigNat_zero(BigNat **zero);

/**
 * Возвращает константу 1.
 * 
 * @note Реализуется через ключевое слово 'static'.
 * 
 * @param zero Полученная константа.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigNat_one(BigNat **one);

/**
 * Сравнивает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @return int Возвращает положительное число, если первое
 *             больше второго; 0, если числа равны; иначе
 *             отрицательное число.
 * 
 * @author
 */
int BigNat_compare(const BigNat *a, const BigNat *b);

/**
 * Проверяет, равно ли число 0.
 * 
 * @note Используйте сравнение чисел и константный 0.
 * 
 * @param a Число.
 * @return int Положительное число, если равно 0. Иначе 0.
 * 
 * @author
 */
int BigNat_is_zero(const BigNat *a);

/**
 * Добавляет к числу 1.
 * 
 * @note Используйте константу 1.
 * 
 * @param a Число.
 * @param c Результат сложения.
 * 
 * @author
 */
void BigNat_add_one(const BigNat *a, BigNat *c);

/**
 * Складывает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Сумма.
 * 
 * @author
 */
void BigNat_sum(const BigNat *a, const  BigNat *b, BigNat *c);

/**
 * Вычитает из первого числа второе.
 * 
 * @note Если первое число меньше второго, то возвращайте ошибку.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Разность.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigNat_sub(const BigNat *a, const  BigNat *b, BigNat *c);

/**
 * Умножает число на цифру (число в промежутке [0, 9]).
 * 
 * @param a Число.
 * @param d Цифра.
 * @param c Результат.
 * 
 * @author
 */
void BigNat_mul_by_digit(const BigNat *a, digit d, BigNat *c);

/**
 * Умножает число на степень 10 (10^k).
 * 
 * @param a Число.
 * @param k Степень 10.
 * @param c Результат.
 * 
 * @author
 */
void BigNat_mul_by_exp10(const BigNat *a, int k, BigNat *c);

/**
 * Умножает два числа.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Произведение.
 * 
 * @author
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
 * 
 * @author
 */
error_t BigNat_sub_proportional(const BigNat *a, const BigNat *b, digit d,
                                BigNat *c);

/**
 * Вычисляет первую цифру деления первого числа на второе, домноженное на
 * 10^k,где k - номер позиции этой цифры (номер считается с нуля).
 * 
 * @note То есть вычисляет первую слева цифру частного.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param d Результат.
 * @param k Количество цифр, на которые сдвигается второе число.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
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
 * 
 * @author
 */
error_t BigNat_div_mod(const BigNat *a, const BigNat *b, BigNat *c, BigNat *r);

/**
 * Делит первое число на второе, возвращает частное/
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigNat_div(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Делит первое число на второе и возвращает остаток.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author
 */
error_t BigNat_mod(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Находит НОД двух чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c НОД.
 * 
 * @author
 */
void BigNat_gcf(const BigNat *a, const BigNat *b, BigNat *c);

/**
 * Находит НОК двух чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c НОК.
 * 
 * @author
 */
void BigNat_lcm(const BigNat *a, const BigNat *b, BigNat *c);

#endif /* !BIGNAT_H */
