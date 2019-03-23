#ifndef MAIN_H
#define MAIN_H

#include "bignumlib-error.h"

#define DASH '-'

/**
 * Точка входа в программу.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Аргументы командной строки. 
 * @return int Код ошибки или 0, если прошло успешно.
 * 
 * @author Dmitry Nikolaev.
 */
int main(int argc, const char **argv);

/**
 * Вызывает действие (операцию).
 * 
 * @param argc Количество аргументов в строке.
 * @param argv Строка аргументов (имя действия, параметры).
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Dmitry Nikolaev.
 */
error_t execute(int argc, const char **argv);

/**
 * Убирает дефисы из начала строки.
 * 
 * @param str Строка.
 * 
 * @author Dmitry Nikolaev.
 */
void remove_dashes(char *str);

/**
 * Находит действие по его имени.
 * 
 * @param name Имя действия.
 * @param i Индекс действия (в массиве actions_list).
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Dmitry Nikolaev.
 */
error_t find_action(const char *name, int *i);

#endif /* !MAIN_H */
