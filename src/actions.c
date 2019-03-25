#include "actions.h"

#include <stdlib.h>
#include <stdio.h>

#include "bigint.h"
#include "bignumlib-error.h"
#include "bignat.h"
#include "utils.h"

error_t help_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t version_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
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

error_t bignat_div_ordered_digit_action(int argc, const char **argv, 
                                        char **res) {
    digit d;
    BigNat *a, *b;
    error_t err;

    *res = (char *)malloc(2 * sizeof(char));
    if (*res == NULL) {
        handle_critical_error(PE_ALLOC);
    } 

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);

    err = BigNat_div_ordered_digit(a, b, &d);
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

error_t bignat_gcf_action(int argc, const char **argv, char **res) {
    BigNat *a, *b, *c;
    error_t err;

    INIT_ACTION_WITH_TWO_PARAMS(BigNat, BigNat, a, b, argv[0], argv[1], err);
    BigNat_new(&c);

    BigNat_gcf(a, b, c);
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

error_t bigint_from_nat_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigint_to_nat_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
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


error_t bigrat_reduce_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_is_int_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_from_int_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_to_int_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_sum_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_sub_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_mul_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigrat_div_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}


error_t bigpol_sum_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_sub_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_mul_scalar_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_mul_expx_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_get_leading_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_get_deg_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_fac_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_mul_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

error_t bigpol_div_action(int argc, const char **argv, char **res) {
    return IE_NOTIMPLEMENTED;
}

// error_t bigpol__action(int argc, const char **argv, char **res);
// error_t bigpol__action(int argc, const char **argv, char **res);
// error_t bigpol__action(int argc, const char **argv, char **res);
// error_t bigpol__action(int argc, const char **argv, char **res);
