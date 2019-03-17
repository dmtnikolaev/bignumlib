#ifndef BIGNUMLIB_ERROR_H
#define BIGNUMLIB_ERROR_H

#define SUCCESS (error_t)0

/**
 * Макрос для проверки отсутствия ошибки.
 */
#define SUCC(err) (err == SUCCESS)

/**
 * Макрос для проверки наличия ошибки.
 */
#define FAIL(err) (err != SUCCESS)

/**
 * Содержит номера всех возможных ошибок. 0 означает отсутствие ошибки.
 * 
 * Префикс "I" означает, что ошибка внутренняя, то есть означает баг в
 * программе. Префиксом "P" обозначаются ошибки, которые могут произойти и
 * о которых необходимо сообщать пользователю.
 */
typedef enum {
    PE_ALLOC = 1,

    IE_INVALIDPARAM = 51,
    IE_NOTIMPLEMENTED = 52,
} error_t;

/**
 * Возвращает строку-сообщение для ошибки.
 * 
 * @param err Код ошибки.
 * @return char* Сообщение.
 * 
 * @author
 */
char *get_error_message(error_t err);

/**
 * Обрабатывает ошибку (выводит в терминал сообщение).
 * 
 * @param err Код ошибки.
 * 
 * @author
 */
void handle_error(error_t err);

#endif /* !BIGNUMLIB_ERROR_H */