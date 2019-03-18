#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdio.h>

#include "bignumlib-error.h"

/**
 * Читает неограниченную строку из файла, автоматически реаллоцируя память.
 * Строка будет читать до ввода переноса строки, который в саму строку
 * добавлен не будет.
 * 
 * @param str Строка.
 * @param str_len Длина стоки.
 * @param f Файл, из которого производится чтение.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
error_t freadline(char **str, size_t *str_len, FILE *f);

/**
 * Аналог freadline для стандартного входа.
 * 
 * @param str Прочитанная строка (можно заранее аллоцировать).
 * @param str_len Длина строки.
 * @return error_t Код ошибки или 0, если успешно.
 */
error_t readline(char **str, size_t *str_len);

#endif /* !UTILS_H */