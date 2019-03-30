#include "actions.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#include "bigint.h"
#include "bignumlib-error.h"
#include "bignat.h"
#include "bigpolynom.h"
#include "bigrat.h"
#include "consts.h"
#include "help.h"
#include "utils.h"

error_t help_action(int argc, const char **argv, char **res) {
    wprintf(L"%ls", help_1);
    wprintf(L"%ls", help_2);
    wprintf(L"%ls", help_3);
    *res = NULL;
    return SUCCESS;
}

error_t version_action(int argc, const char **argv, char **res) {
    wprintf(L"bignumlib v"PURE_C_STRING_FORMAT_SPEC, BIGNUMLIB_VERSION);
    *res = NULL;
    return SUCCESS;
}

error_t bignat_help_action(int argc, const char **argv, char **res) {
    wprintf(L"%ls", nat_help_1);
    wprintf(L"%ls", nat_help_2);
    wprintf(L"%ls", nat_help_3);
    wprintf(L"%ls", nat_help_4);
    *res = NULL;
    return SUCCESS;
}

error_t bignat_compare_action(int argc, const char **argv, char **res) {
    BigNat *a, *b;
    error_t err;

    *res = (char *)malloc(3 * sizeof(char));
    if (*res == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);

    sprintf(*res, "%d", BigNat_compare(a, b));

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);

    return SUCCESS;
}

error_t bignat_is_zero_action(int argc, const char **argv, char **res) {
    BigNat *a;
    error_t err;

    *res = (char *)malloc(2 * sizeof(char));
    if (*res == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    INIT_ACTION_WITH_ONE_PARAM(BigNat, a, argv[0], err);

    sprintf(*res, "%d", BigNat_is_zero(a));

    FIN_ACTION_WITH_ONE_PARAM(BigNat, a);

    return SUCCESS;
}

error_t bignat_add_one_action(int argc, const char **argv, char **res) {
    BigNat *a, *c;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigNat, a, argv[0], err);
    BigNat_new(&c);

    BigNat_add_one(a, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigNat, a);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bignat_sum_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    BigNat_sum(a, b, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bignat_sub_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    err = BigNat_sub(a, b, c);
    if (SUCC(err)) {
        BigNat_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return err;
}

error_t bignat_mul_by_digit_action(int argc, const char **argv, char **res) {
    digit d;
    BigNat *a, *c;
    error_t err;

    err = str_to_digit(argv[1], &d);
    if (FAIL(err)) {
        return err;
    }

    INIT_ACTION_WITH_ONE_PARAM(BigNat, a, argv[0], err);
    BigNat_new(&c);

    BigNat_mul_by_digit(a, d, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigNat, a);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bignat_mul_by_exp10_action(int argc, const char **argv, char **res) {
    int b;
    char *err_buff;
    BigNat *a, *c;
    error_t err;

    b = strtol(argv[1], &err_buff, 10);
    if (*err_buff != 0) {
        return PE_PARSING;
    }
    if (errno == ERANGE || b < 0) {
        return PE_INVALIDPARAM;
    }

    INIT_ACTION_WITH_ONE_PARAM(BigNat, a, argv[0], err);
    BigNat_new(&c);

    BigNat_mul_by_exp10(a, b, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigNat, a);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bignat_mul_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    BigNat_mul(a, b, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bignat_sub_proportional_action(int argc, const char **argv, 
                                       char **res) {
    digit d;
    BigNat *a, *b, *c;
    error_t err;

    err = str_to_digit(argv[2], &d);
    if (FAIL(err)) {
        return err;
    }

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    err = BigNat_sub_proportional(a, b, d, c);
    if (SUCC(err)) {
        BigNat_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return err;
}

error_t bignat_div_first_digit_action(int argc, const char **argv, 
                                        char **res) {
    digit d;
    size_t k;
    BigNat *a, *b;
    error_t err;

    *res = (char *)malloc(2 * sizeof(char));
    if (*res == NULL) {
        handle_critical_error(PE_ALLOC);
    } 

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);

    err = BigNat_div_first_digit(a, b, &d, &k);
    if (SUCC(err)) {
        sprintf(*res, "%d", d);
    }
    
    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);

    return err;
}

error_t bignat_div_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    err = BigNat_div(a, b, c);
    if (SUCC(err)) {
        BigNat_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return err;
}

error_t bignat_mod_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    err = BigNat_mod(a, b, c);
    if (SUCC(err)) {
        BigNat_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return err;
}

error_t bignat_gcd_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    BigNat_gcd(a, b, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bignat_lcm_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    BigNat_lcm(a, b, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bigint_help_action(int argc, const char **argv, char **res) {
    wprintf(L"%ls", int_help_1);
    wprintf(L"%ls", int_help_2);
    *res = NULL;
    return SUCCESS;
}

error_t bigint_abs_action(int argc, const char **argv, char **res) {
    BigInt *a;
    BigNat *c;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigInt, a, argv[0], err);
    BigNat_new(&c);

    BigInt_abs(a, c);
    BigNat_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigInt, a);
    BigNat_destroy(c);

    return SUCCESS;
}

error_t bigint_get_sign_action(int argc, const char **argv, char **res) {
    BigInt *a;
    error_t err;

    *res = (char *)malloc(3 * sizeof(char));
    if (res == NULL) {
        handle_critical_error(PE_ALLOC);
    }

    INIT_ACTION_WITH_ONE_PARAM(BigInt, a, argv[0], err);

    sprintf(*res, "%d", BigInt_get_sign(a));

    FIN_ACTION_WITH_ONE_PARAM(BigInt, a);

    return SUCCESS;
}

error_t bigint_negate_action(int argc, const char **argv, char **res) {
    BigInt *a, *c;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigInt, a, argv[0], err);
    BigInt_new(&c);

    BigInt_negate(a, c);
    BigInt_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigInt, a);
    BigInt_destroy(c);

    return SUCCESS;
}

error_t bigint_sum_action(int argc, const char **argv, char **res) {
    BigInt *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigInt, BigInt, a, b, argv[0], argv[1], err);
    BigInt_new(&c);

    BigInt_add(a, b, c);
    BigInt_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigInt, BigInt, a, b);
    BigInt_destroy(c);

    return SUCCESS;
}

error_t bigint_sub_action(int argc, const char **argv, char **res) {
    BigInt *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigInt, BigInt, a, b, argv[0], argv[1], err);
    BigInt_new(&c);

    BigInt_sub(a, b, c);
    BigInt_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigInt, BigInt, a, b);
    BigInt_destroy(c);

    return SUCCESS;
}

error_t bigint_mul_action(int argc, const char **argv, char **res) {
    BigInt *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigInt, BigInt, a, b, argv[0], argv[1], err);
    BigInt_new(&c);

    BigInt_mul(a, b, c);
    BigInt_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigInt, BigInt, a, b);
    BigInt_destroy(c);

    return SUCCESS;
}

error_t bigint_div_nat_action(int argc, const char **argv, char **res) {
    BigNat *b;
    BigInt *a, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigInt, BigNat, a, b, argv[0], argv[1], err);
    BigInt_new(&c);

    err = BigInt_div_nat(a, b, c);
    if (SUCC(err)) {
        BigInt_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigInt, BigNat, a, b);
    BigInt_destroy(c);

    return err;
}

error_t bigint_mod_nat_action(int argc, const char **argv, char **res) {
    BigNat *b, *c;
    BigInt *a;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigInt, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    err = BigInt_mod_nat(a, b, c);
    if (SUCC(err)) {
        BigNat_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigInt, BigNat, a, b);
    BigNat_destroy(c);

    return err;
}

error_t bigrat_help_action(int argc, const char **argv, char **res) {
    wprintf(L"%ls", rat_help_1);
    wprintf(L"%ls", rat_help_2);
    wprintf(L"%ls", rat_help_3);
    *res = NULL;
    return SUCCESS;
}

error_t bigrat_reduce_action(int argc, const char **argv, char **res) {
    BigRat *a, *c;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigRat, a, argv[0], err);
    BigRat_new(&c);

    BigRat_reduce(a, c);
    BigRat_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigRat, a);
    BigRat_destroy(c);

    return SUCCESS;
}

error_t bigrat_sum_action(int argc, const char **argv, char **res) {
    BigRat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b, argv[0], argv[1], err);
    BigRat_new(&c);

    BigRat_sum(a, b, c);
    BigRat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b);
    BigRat_destroy(c);

    return SUCCESS;
}

error_t bigrat_sub_action(int argc, const char **argv, char **res) {
    BigRat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b, argv[0], argv[1], err);
    BigRat_new(&c);

    BigRat_sub(a, b, c);
    BigRat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b);
    BigRat_destroy(c);

    return SUCCESS;
}

error_t bigrat_mul_action(int argc, const char **argv, char **res) {
    BigRat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b, argv[0], argv[1], err);
    BigRat_new(&c);

    BigRat_mul(a, b, c);
    BigRat_to_string(c, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b);
    BigRat_destroy(c);

    return SUCCESS;
}

error_t bigrat_div_action(int argc, const char **argv, char **res) {
    BigRat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b, argv[0], argv[1], err);
    BigRat_new(&c);

    BigRat_div(a, b, c);
    BigRat_to_string(c, res);

    err = BigRat_div(a, b, c);
    if (SUCC(err)) {
        BigRat_to_string(c, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigRat, BigRat, a, b);
    BigRat_destroy(c);

    return err;
}

error_t bigpol_help_action(int argc, const char **argv, char **res) {
    wprintf(L"%ls", pol_help_1);
    *res = NULL;
    return SUCCESS;
}

error_t bigpol_sum_action(int argc, const char **argv, char **res) {
    BigPol *f, *g, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g, argv[0], argv[1], err);
    BigPol_new(&h);

    BigPol_sum(f, g, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g);
    BigPol_destroy(h);

    return SUCCESS;
}

error_t bigpol_sub_action(int argc, const char **argv, char **res) {
    BigPol *f, *g, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g, argv[0], argv[1], err);
    BigPol_new(&h);

    BigPol_sub(f, g, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g);
    BigPol_destroy(h);

    return SUCCESS;
}

error_t bigpol_mul_scalar_action(int argc, const char **argv, char **res) {
    BigRat *c;
    BigPol *f, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigRat, f, c, argv[0], argv[1], err);
    BigPol_new(&h);

    BigPol_mul_scalar(f, c, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigRat, f, c);
    BigPol_destroy(h);

    return SUCCESS;
}

error_t bigpol_mul_expx_action(int argc, const char **argv, char **res) {
    size_t k;
    BigPol *f, *h;
    error_t err;

    if (sscanf(argv[1], "%"SIZE_T_FORMAT_SPEC"x", &k) != 1) {
        return PE_PARSING;
    }

    INIT_ACTION_WITH_ONE_PARAM(BigPol, f, argv[0], err);
    BigPol_new(&h);

    BigPol_mul_expx(f, k, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_ONE_PARAM(BigPol, f);
    BigPol_destroy(h);

    return SUCCESS;
}

error_t bigpol_get_leading_action(int argc, const char **argv, char **res) {
    BigRat *a_n;
    BigPol *f;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigPol, f, argv[0], err);
    BigRat_new(&a_n);

    BigPol_get_leading(f, a_n);
    BigRat_to_string(a_n, res);

    FIN_ACTION_WITH_ONE_PARAM(BigPol, f);
    BigRat_destroy(a_n);

    return SUCCESS;
}

error_t bigpol_get_deg_action(int argc, const char **argv, char **res) {
    size_t deg;
    BigPol *f;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigPol, f, argv[0], err);

    BigPol_get_deg(f, &deg);
    *res = (char *)malloc(SIZE_T_MAX_DIGITS * sizeof(char));
    if (*res == NULL) {
        handle_critical_error(PE_ALLOC);
    }
    sprintf(*res, "%"SIZE_T_FORMAT_SPEC"x", deg);

    FIN_ACTION_WITH_ONE_PARAM(BigPol, f);

    return SUCCESS;
}

error_t bigpol_fac_action(int argc, const char **argv, char **res) {
    BigRat *c;
    BigPol *f, *h;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigPol, f, argv[0], err);
    BigRat_new(&c);
    BigPol_new(&h);

    BigPol_fac(f, h, c);
    BigRat_to_string(c, res);

    FIN_ACTION_WITH_ONE_PARAM(BigPol, f);
    BigRat_destroy(c);
    BigPol_destroy(h);

    return SUCCESS;
}

error_t bigpol_mul_action(int argc, const char **argv, char **res) {
    BigPol *f, *g, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g, argv[0], argv[1], err);
    BigPol_new(&h);

    BigPol_mul(f, g, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g);
    BigPol_destroy(h);

    return SUCCESS;
}

error_t bigpol_div_action(int argc, const char **argv, char **res) {
    BigPol *f, *g, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g, argv[0], argv[1], err);
    BigPol_new(&h);

    err = BigPol_div(f, g, h);
    if (SUCC(err)) {
        BigPol_to_string(h, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g);
    BigPol_destroy(h);

    return err;
}

error_t bigpol_mod_action(int argc, const char **argv, char **res) {
    BigPol *f, *g, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g, argv[0], argv[1], err);
    BigPol_new(&h);

    err = BigPol_mod(f, g, h);
    if (SUCC(err)) {
        BigPol_to_string(h, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g);
    BigPol_destroy(h);

    return err;
}

error_t bigpol_gcd_action(int argc, const char **argv, char **res) {
    BigPol *f, *g, *h;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g, argv[0], argv[1], err);
    BigPol_new(&h);

    err = BigPol_gcd(f, g, h);
    if (SUCC(err)) {
        BigPol_to_string(h, res);
    }

    FIN_ACTION_WITH_TWO_PARAMS(BigPol, BigPol, f, g);
    BigPol_destroy(h);
    
    return err;
}

error_t bigpol_der_action(int argc, const char **argv, char **res) {
    BigPol *f, *h;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigPol, f, argv[0], err);
    BigPol_new(&h);

    BigPol_der(f, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_ONE_PARAM(BigPol, f);
    BigPol_destroy(h);
    
    return SUCCESS;
}

error_t bigpol_nmr_action(int argc, const char **argv, char **res) {
    BigPol *f, *h;
    error_t err;

    INIT_ACTION_WITH_ONE_PARAM(BigPol, f, argv[0], err);
    BigPol_new(&h);

    BigPol_nmr(f, h);
    BigPol_to_string(h, res);

    FIN_ACTION_WITH_ONE_PARAM(BigPol, f);
    BigPol_destroy(h);

    return SUCCESS;
}
