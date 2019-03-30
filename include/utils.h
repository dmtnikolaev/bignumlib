#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdio.h>

#include "bignat.h"
#include "bignumlib-error.h"

/**
 * Макрос, возвращающий максимальное из двух чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @return a, если a > b; b, если b >= a;
 * 
 * @author Stepan Repin.
 */
#define MAX(a, b) ( ((a)>(b)) ? (a) : (b) )

/**
 * Читает неограниченную строку из файла, автоматически реаллоцируя память.
 * Строка будет читать до ввода переноса строки, который в саму строку
 * добавлен не будет.
 * 
 * @param str Строка.
 * @param str_len Длина стоки.
 * @param f Файл, из которого производится чтение.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Stepan Repin.
 */
error_t freadline(char **str, size_t *str_len, FILE *f);

/**
 * Аналог freadline для стандартного входа.
 * 
 * @param str Прочитанная строка (можно заранее аллоцировать).
 * @param str_len Длина строки.
 * @return error_t Код ошибки или 0, если успешно.
 * 
 * @author Stepan Repin.
 */
error_t readline(char **str, size_t *str_len);

/**
 * Переставляет a и b местами.
 * 
 * @param a Первый объект.
 * @param b Второй объект.
 * 
 * @author Stepan Repin.
 */
void swap(void *a, void *b);

/**
 * Преобразует цифру в символ.
 * 
 * @param d Цифра.
 * @return char Символ.
 * 
 * @author Stepan Repin.
 */
char digit_to_char(digit d);

/**
 * Преобразует строку в число [0..9].
 * 
 * @param str Строка.
 * @param d Число.
 * @return error_t Код ошибки или 0, если успешно.
 * 
 * @author Dmitry Nikolaev.
 */
error_t str_to_digit(const char *str, digit *d);

/**
 * Преобразует символ в число [0..9].
 * 
 * @param ch Символ.
 * @param d Число.
 * @return error_t Код ошибки или 0, если успешно.
 * 
 * @author Dmitry Nikolaev.
 */
error_t char_to_digit(const char ch, digit *d);

/**
 * Подсчитывает количество вхождений символа в строке.
 * 
 * @param str Строка.
 * @param s Символ.
 * @return size_t Количество вхождений.
 */
size_t count_occurs(const char *str, char s);

#endif /* !UTILS_H */

