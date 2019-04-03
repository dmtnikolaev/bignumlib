#ifndef CONSTS_H
#define CONSTS_H

#define BIGNUMLIB_VERSION "1.1"

#define SIZE_T_MAX_DIGITS ( 241 * sizeof(size_t) / 100 + 1 )

#ifdef WINDOWS
    #define PURE_C_STRING_FORMAT_SPEC L"%S"

    // see https://stackoverflow.com/a/43789115
    #define SIZE_T_FORMAT_SPEC "I"
#elif LINUX
    #define PURE_C_STRING_FORMAT_SPEC L"%s"
    #define SIZE_T_FORMAT_SPEC "z"
#else
    #error "unknown platform" 
#endif

#endif /* !CONSTS_H */
