#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

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
int main(int argc, char **argv);

/**
 * Вызывает действие (операцию).
 * 
 * @param argc Количество аргументов в строке.
 * @param argv Строка аргументов (имя действия, параметры).
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Dmitry Nikolaev.
 */
error_t execute(int argc, char **argv);

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

/**
 * Читает аргументы из stdin и вызывает execute.
 * 
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Stepan Repin.
 */
error_t debug_execute();

/**
 * Читает аргументы из stdin.
 * 
 * @param argc Количество аргументов.
 * @param argv Аргументы.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Stepan Repin.
 */
error_t read_argv_from_user(int *argc, char ***argv);

/**
 * Читает одну строку из stdin, напечатав перед этим prompt.
 * 
 * @param arg Прочитанная строка.
 * @param arg_len Длина прочитанной строки.
 * @param prompt Строка, печатающаяся перед вводом.
 * @return error_t Код ошибки или 0, если прошло успешно.
 * 
 * @author Stepan Repin.
 */
error_t read_arg_from_stdin(char **arg, size_t *arg_len, const char *prompt);

#endif /* !MAIN_H */
