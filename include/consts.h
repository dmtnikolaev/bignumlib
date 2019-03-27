#ifndef CONSTS_H
#define CONSTS_H

#define BIGNUMLIB_VERSION "0.9"

#ifdef WINDOWS
    #define PURE_C_STRING_FORMAT_SPEC L"%S"
#elif LINUX
    #define PURE_C_STRING_FORMAT_SPEC L"%s"
#else
    #error "unknown platform" 
#endif

#endif /* !CONSTS_H */
