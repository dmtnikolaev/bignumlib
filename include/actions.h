#ifndef ACTIONS_H
#define ACTIONS_H

#include "bignumlib-error.h"

#define NAME_LEN_MAX 64
#define ACTIONS_LEN_MAX 64

#define INIT_ACTION_WITH_ONE_PARAM(T_a, a, a_str, err) do { \
        T_a##_new(&(a));                                    \
                                                            \
        err = T_a##_from_string(a, a_str);                  \
        if (FAIL(err)) {                                    \
            T_a##_destroy(a);                               \
            return err;                                     \
        }                                                   \
    }                                                       \
    while(0);                  

#define INIT_ACTION_WITH_TWO_PARAMS(T_a, T_b, a, b, a_str, b_str, err) do { \
        T_a##_new(&(a));                                                    \
        T_b##_new(&(b));                                                    \
                                                                            \
        err = T_a##_from_string(a, a_str);                                  \
        if (FAIL(err)) {                                                    \
            T_a##_destroy(a);                                               \
            T_b##_destroy(b);                                               \
            return err;                                                     \
        }                                                                   \
                                                                            \
        err = T_b##_from_string(b, b_str);                                  \
        if (FAIL(err)) {                                                    \
            T_a##_destroy(a);                                               \
            T_b##_destroy(b);                                               \
            return err;                                                     \
        }                                                                   \
    }                                                                       \
    while(0);

#define FIN_ACTION_WITH_ONE_PARAM(T_a, a) do { \
        T_a##_destroy(a);                      \
    }                                          \
    while(0);

#define FIN_ACTION_WITH_TWO_PARAMS(T_a, T_b, a, b) do { \
        T_a##_destroy(a);                               \
        T_b##_destroy(b);                               \
    }                                                   \
    while(0);

/**
 * Функция-обработчик действия.
 */
typedef error_t (*action)(int argc, const char **argv, char **res);

/**
 * Информационные комманды.
 * 
 * @param argc Количество аргументов.
 * @param argv Массив строк аргументов.
 * @param res Строка, представляющая собой результат работы комманды.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
//@{
error_t help_action(int argc, const char **argv, char **res);
error_t version_action(int argc, const char **argv, char **res);
//@}

/**
 * Комманды для модуля BigNat.
 * 
 * @param argc Количество аргументов.
 * @param argv Массив строк аргументов.
 * @param res Строка, представляющая собой результат работы комманды.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
//@{
error_t bignat_compare_action(int argc, const char **argv, char **res);
error_t bignat_is_zero_action(int argc, const char **argv, char **res);
error_t bignat_add_one_action(int argc, const char **argv, char **res);
error_t bignat_sum_action(int argc, const char **argv, char **res);
error_t bignat_sub_action(int argc, const char **argv, char **res);
error_t bignat_mul_by_digit_action(int argc, const char **argv, char **res);
error_t bignat_mul_by_exp10_action(int argc, const char **argv, char **res);
error_t bignat_mul_action(int argc, const char **argv, char **res);
error_t bignat_sub_proportional_action(int argc, const char **argv, 
                                       char **res);
error_t bignat_div_ordered_digit_action(int argc, const char **argv, 
                                        char **res);
error_t bignat_div_action(int argc, const char **argv, char **res);
error_t bignat_mod_action(int argc, const char **argv, char **res);
error_t bignat_gcf_action(int argc, const char **argv, char **res);
error_t bignat_lcm_action(int argc, const char **argv, char **res);
//@}

/**
 * Комманды для модуля BigInt.
 * 
 * @param argc Количество аргументов.
 * @param argv Массив строк аргументов.
 * @param res Строка, представляющая собой результат работы комманды.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
//@{
error_t bigint_abs_action(int argc, const char **argv, char **res);
error_t bigint_get_sign_action(int argc, const char **argv, char **res);
error_t bigint_negate_action(int argc, const char **argv, char **res);
error_t bigint_from_nat_action(int argc, const char **argv, char **res);
error_t bigint_to_nat_action(int argc, const char **argv, char **res);
error_t bigint_sum_action(int argc, const char **argv, char **res);
error_t bigint_sub_action(int argc, const char **argv, char **res);
error_t bigint_mul_action(int argc, const char **argv, char **res);
error_t bigint_div_nat_action(int argc, const char **argv, char **res);
error_t bigint_mod_nat_action(int argc, const char **argv, char **res);
//@}

/**
 * Комманды для модуля BigRat.
 * 
 * @param argc Количество аргументов.
 * @param argv Массив строк аргументов.
 * @param res Строка, представляющая собой результат работы комманды.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
//@{
error_t bigrat_reduce_action(int argc, const char **argv, char **res);
error_t bigrat_is_int_action(int argc, const char **argv, char **res);
error_t bigrat_from_int_action(int argc, const char **argv, char **res);
error_t bigrat_to_int_action(int argc, const char **argv, char **res);
error_t bigrat_sum_action(int argc, const char **argv, char **res);
error_t bigrat_sub_action(int argc, const char **argv, char **res);
error_t bigrat_mul_action(int argc, const char **argv, char **res);
error_t bigrat_div_action(int argc, const char **argv, char **res);
//@}

/**
 * Комманды для модуля BigPol.
 * 
 * @param argc Количество аргументов.
 * @param argv Массив строк аргументов.
 * @param res Строка, представляющая собой результат работы комманды.
 * @return error_t Код ошибки или 0, если прошло успешно.
 */
//@{
error_t bigpol_sum_action(int argc, const char **argv, char **res);
error_t bigpol_sub_action(int argc, const char **argv, char **res);
error_t bigpol_mul_scalar_action(int argc, const char **argv, char **res);
error_t bigpol_mul_expx_action(int argc, const char **argv, char **res);
error_t bigpol_get_leading_action(int argc, const char **argv, char **res);
error_t bigpol_get_deg_action(int argc, const char **argv, char **res);
error_t bigpol_fac_action(int argc, const char **argv, char **res);
error_t bigpol_mul_action(int argc, const char **argv, char **res);
error_t bigpol_div_action(int argc, const char **argv, char **res);
error_t bigpol_mod_action(int argc, const char **argv, char **res);
error_t bigpol_gcd_action(int argc, const char **argv, char **res);
error_t bigpol_der_action(int argc, const char **argv, char **res);
error_t bigpol_nmr_action(int argc, const char **argv, char **res);
//@}

/**
 * Структура, ответственная за связь между именами комманд и указателями на
 * функции вызова.
 */
static const struct {
    /**
     * Имя комманды.
     */
    char name[NAME_LEN_MAX];

    /**
     * Указатель на функцию вызова действия.
     */
    action action;

    /**
     * Количество внешних аргументов, необходимых для вызова.
     */
    int param_count;
} actions_list[ACTIONS_LEN_MAX] = {
    {"help", help_action, 0},
    {"version", version_action, 0},

    {"nat.compare", bignat_compare_action, 2},
    {"nat.iszero", bignat_is_zero_action, 1},
    {"nat.addone", bignat_add_one_action, 1},
    {"nat.sum", bignat_sum_action, 2},
    {"nat.sub", bignat_sub_action, 2},
    {"nat.mulbydigit", bignat_mul_by_digit_action, 2},
    {"nat.mulbyexp10", bignat_mul_by_exp10_action, 2},
    {"nat.mul", bignat_mul_action, 2},
    {"nat.subproportional", bignat_sub_proportional_action, 3},
    {"nat.divordereddigit", bignat_div_ordered_digit_action, 2},
    {"nat.div", bignat_div_action, 2},
    {"nat.mod", bignat_mod_action, 2},
    {"nat.gcf", bignat_gcf_action, 2},
    {"nat.lcm", bignat_lcm_action, 2},

    {"int.abs", bigint_abs_action, 1},
    {"int.sign", bigint_get_sign_action, 1},
    {"int.negate", bigint_negate_action, 1},
    {"int.fromnat", bigint_from_nat_action, 1},
    {"int.tonat", bigint_to_nat_action, 1},
    {"int.sum", bigint_sum_action, 2},
    {"int.sub", bigint_sub_action, 2},
    {"int.mul", bigint_mul_action, 2},
    {"int.divnat", bigint_div_nat_action, 2},
    {"int.modnat", bigint_mod_nat_action, 2},

    {"rat.reduce", bigrat_reduce_action, 1},
    {"rat.isint", bigrat_is_int_action, 1},
    {"rat.fromint", bigrat_from_int_action, 1},
    {"rat.toint", bigrat_to_int_action, 1},
    {"rat.sum", bigrat_sum_action, 2},
    {"rat.sub", bigrat_sub_action, 2},
    {"rat.mul", bigrat_mul_action, 2},
    {"rat.div", bigrat_div_action, 2},

    {"pol.sum", bigpol_sum_action, 2},
    {"pol.sub", bigpol_sub_action, 2},
    {"pol.mulscalar", bigpol_mul_scalar_action, 2},
    {"pol.mulexpx", bigpol_mul_expx_action, 2},
    {"pol.leading", bigpol_get_leading_action, 1},
    {"pol.deg", bigpol_get_deg_action, 1},
    {"pol.fac", bigpol_fac_action, 1},
    {"pol.mul", bigpol_mul_action, 2},
    {"pol.div", bigpol_div_action, 2},
    {"pol.mod", bigpol_mod_action, 2},
    {"pol.gcd", bigpol_gcd_action, 2},
    {"pol.der", bigpol_der_action, 1},
    {"pol.nmr", bigpol_nmr_action, 1},
};

#endif /* !ACTIONS_H */
