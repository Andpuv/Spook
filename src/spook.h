# ifndef __SPOOK_H
#   define __SPOOK_H

#   define __SPOOK_IN
#   define __SPOOK_OUT
#   define __SPOOK_INOUT

#   include <stdint.h>

typedef uint8_t  u_byte_t;
typedef uint16_t u_word_t;
typedef uint32_t u_dword_t;
typedef uint64_t u_qword_t;

#   define U_BYTE(n)   UINT8_C(n)
#   define U_WORD(n)   UINT16_C(n)
#   define U_DWORD(n)  UINT32_C(n)
#   define U_QWORD(n)  UINT64_C(n)

#   define U_BYTE_MAX  UINT8_MAX
#   define U_WORD_MAX  UINT16_MAX
#   define U_DWORD_MAX UINT32_MAX
#   define U_QWORD_MAX UINT64_MAX

typedef  int8_t  s_byte_t;
typedef  int16_t s_word_t;
typedef  int32_t s_dword_t;
typedef  int64_t s_qword_t;

#   define S_BYTE(n)   INT8_C(n)
#   define S_WORD(n)   INT16_C(n)
#   define S_DWORD(n)  INT32_C(n)
#   define S_QWORD(n)  INT64_C(n)

#   define S_BYTE_MIN  INT8_MIN
#   define S_WORD_MIN  INT16_MIN
#   define S_DWORD_MIN INT32_MIN
#   define S_QWORD_MIN INT64_MIN

#   define S_BYTE_MAX  INT8_MAX
#   define S_WORD_MAX  INT16_MAX
#   define S_DWORD_MAX INT32_MAX
#   define S_QWORD_MAX INT64_MAX

#   include "spook-config.h"

#   if 4 == __SIZEOF_POINTER__
#     define __U_ADDR_T   u_dword_t
#     define __U_SIZE_T   u_dword_t
#     define __U_ADDR     U_DWORD
#     define __U_SIZE     U_DWORD
#     define __U_ADDR_MAX U_DWORD_MAX
#     define __U_SIZE_MAX U_DWORD_MAX
#     define __S_ADDR_T   s_dword_t
#     define __S_SIZE_T   s_dword_t
#     define __S_ADDR     S_DWORD
#     define __S_SIZE     s_DWORD
#     define __S_ADDR_MIN S_DWORD_MIN
#     define __S_SIZE_MIN S_DWORD_MIN
#     define __S_ADDR_MAX S_DWORD_MAX
#     define __S_SIZE_MAX S_DWORD_MAX
#   else
#     define __U_ADDR_T   u_qword_t
#     define __U_SIZE_T   u_qword_t
#     define __U_ADDR     U_QWORD
#     define __U_SIZE     U_QWORD
#     define __U_ADDR_MAX U_QWORD_MAX
#     define __U_SIZE_MAX U_QWORD_MAX
#     define __S_ADDR_T   s_qword_t
#     define __S_SIZE_T   s_qword_t
#     define __S_ADDR     S_QWORD
#     define __S_SIZE     s_QWORD
#     define __S_ADDR_MIN S_QWORD_MIN
#     define __S_SIZE_MIN S_QWORD_MIN
#     define __S_ADDR_MAX S_QWORD_MAX
#     define __S_SIZE_MAX S_QWORD_MAX
#   endif

typedef __U_ADDR_T u_addr_t;
typedef __U_SIZE_T u_size_t;

#   define U_ADDR(n)  __U_ADDR(n)
#   define U_SIZE(n)  __U_SIZE(n)

#   define U_ADDR_MAX __U_ADDR_MAX
#   define U_SIZE_MAX __U_SIZE_MAX

typedef __S_ADDR_T s_addr_t;
typedef __S_SIZE_T s_size_t;

#   define S_ADDR(n)  __S_ADDR(n)
#   define S_SIZE(n)  __S_SIZE(n)

#   define S_ADDR_MIN __S_ADDR_MIN
#   define S_SIZE_MIN __S_SIZE_MIN

#   define S_ADDR_MAX __S_ADDR_MAX
#   define S_SIZE_MAX __S_SIZE_MAX

#   undef __U_ADDR_T
#   undef __U_SIZE_T
#   undef __U_ADDR
#   undef __U_SIZE
#   undef __U_ADDR_MAX
#   undef __U_SIZE_MAX
#   undef __S_ADDR_T
#   undef __S_SIZE_T
#   undef __S_ADDR
#   undef __S_SIZE
#   undef __S_ADDR_MIN
#   undef __S_SIZE_MIN
#   undef __S_ADDR_MAX
#   undef __S_SIZE_MAX

#   include "spook-version.h"

#   define __SPOOK__ __SPOOK_VERSION

# endif
