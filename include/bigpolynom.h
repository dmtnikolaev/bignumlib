//
// @author Danil Novikov.
//

#ifndef BIGPOLYNOM_H
#define BIGPOLYNOM_H

#include <stddef.h>

#include "bignumlib-error.h"
#include "bigrat.h"

/**
 * Представляет многочлен с длинными рациональными коэффициентами.
 */
typedef struct {
    /**
     * Коэффициенты многочлена, индекс - степень, при которой коэффициент
     * находится.
     */
    BigRat **coeffs;

    /**
     * Количество коэффициентов (также степень многочлена + 1).
     */
    size_t size;

    /**
     * Количество коэффициентов, для которых уже выдела память
     * (то есть выделено памяти может быть больше, чем требуется).
     */
    size_t available_size;
} BigPol;

/**
 * Создает новый многочлен, равный 0.
 * 
 * @param f Новый многочлен.
 */
void BigPol_new(BigPol **f);

/**
 * Очищает память, выделенную под многочлен.
 * 
 * @param f Многочлен.
 */
void BigPol_destroy(BigPol *f);

/**
 * Увеличивает количество коэффициентов до new_size. Новые коэффициенты
 * будут обнулены.
 * 
 * Если new_size <= f->size, то ничего не происходит.
 * 
 * @param f Многочлен.
 * @param new_size Новое количество коэффициентов.
 */
void BigPol_resize(BigPol *f, const size_t new_size);

/**
 * Преобразует строку в многочлен.
 * 
 * @param f Многочлен.
 * @param str Строка.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigPol_from_string(BigPol *f, const char *str);

/**
 * Преобразует многочлен в строку.
 * 
 * @param f Многочлен.
 * @param str Строка.
 */
void BigPol_to_string(const BigPol *f, char **str);

/**
 * Складывает два многочлена.
 * 
 * @param f Первый многочлен.
 * @param g Второй многочлен.
 * @param h Сумма.
 */
void BigPol_sum(const BigPol *f, const BigPol *g, BigPol *h);

/**
 * Вычитает из первого многочлена второй.
 * 
 * @param f Первый многочлен.
 * @param g Второй многочлен.
 * @param h Разность.
 */
void BigPol_sub(const BigPol *f, const BigPol *g, BigPol *h);

/**
 * Умножает многочлен на скаляр (рациональное число).
 * 
 * @param f Многочлен.
 * @param c Скаляр.
 * @param h Результат.
 */
void BigPol_mul_scalar(const BigPol *f, const BigRat *c, BigPol *h);

/**
 * Умножение многочлена на одночлен x^k.
 * 
 * @param f Многочлен.
 * @param k Степень одночлена.
 * @param h Результат.
 */
void BigPol_mul_expx(const BigPol *f, const BigNat *k, BigPol *h);

/**
 * Возвращает старший коэффициент многочлена.
 * 
 * @param f Многочлен.
 * @param a_n Старший коэффициент.
 */
void BigPol_get_leading(const BigPol *f, BigRat *a_n);

/**
 * Возвращает степень многочлена.
 * 
 * @param f Многочлен.
 * @param deg Степень.
 */
void BigPol_get_deg(const BigPol *f, BigNat *deg);

/**
 * Выносит из многочлена НОК знаменателей коэффициентов и НОД числителей.
 * 
 * @param f Многочлен.
 * @param h Многочлен с вынесенными НОК и НОД знаменателей и числителей
 *          соответственно.
 * @param c Дробь, полученная делением НОД числителей коэффициентов на
 *          НОК знаменателей многочлена.
 */
void BigPol_fac(const BigPol *f, BigPol *h, BigRat *c);

/**
 * Умножает два многочлена.
 * 
 * @param f Первый многочлен.
 * @param g Второй многочлен.
 * @param h Произведение.
 */
void BigPol_mul(const BigPol *f, const BigPol *g, BigPol *h);

/**
 * Возвращает частное от деления многочлена на многочлен при делении с остатком.
 * 
 * @param f Первый многочлен.
 * @param g Второй многочлен.
 * @param h Частное.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigPol_div(const BigPol *f, const BigPol *g, BigPol *h);

/**
 * Возвращает остаток от деления многочлена на многочлен.
 * 
 * @param f Первый многочлен.
 * @param g Второй многочлен.
 * @param h Остаток.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigPol_mod(const BigPol *f, const BigPol *g, BigPol *h);

/**
 * Возвращает НОД двух многочленов.
 * 
 * @param f Первый многочлен.
 * @param g Второй многочлен.
 * @param h НОД
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t BigPol_gcd(const BigPol *f, const BigPol *g, BigPol *h);

/**
 * Находит производную от многочлена.
 * 
 * @param f Многочлен.
 * @param h Производная.
 */
void BigPol_der(const BigPol *f, BigPol *h);

/**
 * Преобразует многочлен в другой, не имеющий кратных корней.
 * 
 * @param Многочлен
 * @param Многочлен без кратных корней, но имеющий те же корни, что и исходный.
 */
void BigPol_nmr(const BigPol *f, BigPol *h);

#endif /* !BIGPOLYNOM_H */