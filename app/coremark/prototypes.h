#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#ifdef __GNUC__
#define va_start(ap, argN) __builtin_va_start(ap, argN)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)
#define va_copy(dst, src) __builtin_va_copy(dst, src)

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
typedef   __INT8_TYPE__ int8_t;
typedef  __INT16_TYPE__ int16_t;
typedef  __INT32_TYPE__ int32_t;
typedef  __INT64_TYPE__ int64_t;
typedef  __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;
typedef __SIZE_TYPE__ size_t;
#else
#error "GNUC compatible compiler is required"
#endif

#define NULL ((void*)0)

#endif /* !PROTOTYPES_H */
