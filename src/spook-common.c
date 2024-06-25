# include "spook.h"
# include <ctype.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define ERRNO(err, res) \
  do {                   \
    errno = err;         \
    return res;          \
  } while ( 0 )

__SPOOK_PUBLIC void * spook_alloc (
  __SPOOK_IN    u_size_t bytes
)
{
  if ( !bytes )
    ERRNO(EINVAL, NULL);

  void * ptr = malloc(bytes);

  if ( !ptr ) {
    /* /discard/ */ fprintf(stderr,
      "[ FATAL ] Cannot allocate %zu byte(s): "
      "%s.",
      (size_t)bytes, strerror(errno)
    );

    abort();
  }

  return ptr;
}

__SPOOK_PUBLIC void * spook_realloc (
  __SPOOK_IN    void *   ptr,
  __SPOOK_IN    u_size_t bytes
)
{
  if ( !bytes )
    return spook_dealloc(ptr);

  ptr = realloc(ptr, bytes);

  if ( !ptr ) {
    /* /discard/ */ fprintf(stderr,
      "[ FATAL ] Cannot allocate %zu byte(s): "
      "%s.",
      (size_t)bytes, strerror(errno)
    );

    abort();
  }

  return ptr;
}

__SPOOK_PUBLIC void * spook_dealloc (
  __SPOOK_IN    void *   ptr
)
{
  if ( ptr ) {
    free(ptr);
  }

  return NULL;
}

__SPOOK_PRIVATE int str_to_uint (
  __SPOOK_IN    char *       str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    u_qword_t *  num
)
{
  /* extract the radix */

  if ( !rad ) {
    if ( '0' == *str ) {
      ++str;

      if ( 'b' == *str || 'B' == *str ) {
        ++str;
        rad = 2;
      } else if ( 'o' == *str || 'O' == *str ) {
        ++str;
        rad = 8;
      } else if ( 'x' == *str || 'X' == *str ) {
        ++str;
        rad = 16;
      } else {
        rad = 8;
      }
    } else {
      rad = 10;

      char * cur = str;
      int    num = 0;

      while ( *cur && isdigit(*cur) ) {
        num *= rad;
        num += (int)( *cur++ - '0' );
      }

      if ( 'r' == *cur || 'R' == *cur ) {
        rad = num;
        str = ++cur;
      }
    }
  } else {
    if ( rad < 2 || 36 < rad )
      ERRNO(EINVAL, -2);
  }

  /* extract the number */

  int       tmp_idx = -1;
  u_qword_t tmp_num = U_QWORD(0);

  while ( *str ) {
    int dig = -1;

    if ( '0' <= *str && *str <= '9' ) {
      dig = (int)( *str - '0' );
    } else if ( 'A' <= *str && *str <= 'Z' ) {
      dig = (int)( *str - 'A' ) + 10;
    } else if ( 'a' <= *str && *str <= 'z' ) {
      dig = (int)( *str - 'a' ) + 10;
    } else if ( '_' == *str ) {
      if ( tmp_idx < 0 )
        ERRNO(EINVAL, -3);

      tmp_idx = 1;

      ++str;
      continue;
    }

    if ( dig < 0 || rad <= dig )
      break;

    tmp_idx  = 0;
    tmp_num *= rad;
    tmp_num += dig;

    ++str;
  }

  if ( tmp_idx )
    ERRNO(EINVAL, -4);

  /* store results */

  if ( endptr ) {
    *endptr = str;
  }

  if ( num ) {
    *num = tmp_num;
  }

  return 0;
}

__SPOOK_PRIVATE int str_to_sint (
  __SPOOK_IN    char *       str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    s_qword_t *  num
)
{
  s_qword_t sgn = S_QWORD(1);

  if ( '-' == *str ) {
    ++str;
    sgn = -sgn;
  } else if ( '+' == *str ) {
    ++str;
  }

  u_qword_t tmp_num;

  int res = str_to_uint(str, endptr, rad, &tmp_num);

  if ( res )
    return res;

  if ( 0 < sgn ) {
    if ( (u_qword_t)S_QWORD_MAX < tmp_num )
      ERRNO(ERANGE, -5);
  } else {
    if ( -(u_qword_t)S_QWORD_MIN < tmp_num )
      ERRNO(ERANGE, -6);
  }

  if ( num ) {
    *num = sgn * (s_qword_t)tmp_num;
  }

  return 0;
}

__SPOOK_PUBLIC int spook_str_to_uint (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    u_qword_t *  num
)
{
  if ( !str )
    ERRNO(EINVAL, -1);

  char * cur = (char *)str;

  while ( isspace(*cur) ) {
    ++cur;
  }

  return str_to_uint(cur, endptr, rad, num);
}

__SPOOK_PUBLIC int spook_str_to_sint (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    s_qword_t *  num
)
{
  if ( !str )
    ERRNO(EINVAL, -1);

  char * cur = (char *)str;

  while ( isspace(*cur) ) {
    ++cur;
  }

  return str_to_sint(cur, endptr, rad, num);
}

__SPOOK_PUBLIC int spook_str_to_size (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    u_size_t *   num
)
{
  u_qword_t tmp_num    = U_QWORD(0);
  char *    tmp_endptr = (char *)NULL;

  int res = spook_str_to_uint(str, &tmp_endptr, rad, &tmp_num);

  if ( res )
    return res;

  if ( tmp_endptr && *tmp_endptr ) {
    int  muln = 0;
    char mulc = tmp_endptr[ 0 ];
    char pow2 = mulc ? ( 'i' == tmp_endptr[ 1 ] ) : 0;

    switch ( mulc ) {
    case 'k': /* /fallthrough/ */
    case 'K': { muln = pow2 ? 10 :  3; tmp_endptr += 1 + pow2; } break;
    case 'M': { muln = pow2 ? 20 :  6; tmp_endptr += 1 + pow2; } break;
    case 'G': { muln = pow2 ? 30 :  9; tmp_endptr += 1 + pow2; } break;
    case 'T': { muln = pow2 ? 40 : 12; tmp_endptr += 1 + pow2; } break;
    case 'P': { muln = pow2 ? 50 : 15; tmp_endptr += 1 + pow2; } break;
    case 'E': { muln = pow2 ? 60 : 18; tmp_endptr += 1 + pow2; } break;
    }

    if ( muln ) {
      if ( pow2 ) {
        tmp_num <<= muln;
      } else {
        u_qword_t mulv = U_QWORD(1);

        while ( muln > 0 ) {
          mulv *= U_QWORD(1000);
          muln -= 3;
        }

        tmp_num *= mulv;
      }
    }
  }

  if ( num ) {
    *num = (u_size_t)tmp_num;
  }

  if ( endptr ) {
    *endptr = tmp_endptr;
  }

  return 0;
}

__SPOOK_PUBLIC int spook_str_to_chr (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr
)
{
  if ( !str )
    ERRNO(EINVAL, -1);

  char * cur = (char *)str;
  int    chr = *cur++;

  if ( '\\' == chr ) {
    chr = *cur++;

    switch ( chr ) {
    case 'a'  : { chr = '\a';   } break;
    case 'c'  : { chr = '\b';   } break;
    case 't'  : { chr = '\t';   } break;
    case 'n'  : { chr = '\n';   } break;
    case 'v'  : { chr = '\v';   } break;
    case 'f'  : { chr = '\f';   } break;
    case 'r'  : { chr = '\r';   } break;
    case 'e'  : { chr = '\x1B'; } break;
    case 's'  : { chr = ' ';    } break;
    case '!'  : { chr = '!';    } break;
    case '?'  : { chr = '?';    } break;
    case '\'' : { chr = '\'';   } break;
    case '\"' : { chr = '\"';   } break;
    case 'g'  : { chr = '`';    } break;
    case 'd'  : { chr = '\x7F'; } break;

    case '0'  :
    case 'b'  : case 'B' :
    case 'x'  : case 'X' :
    default   : {
      int rad =
        ( '0' == chr               ) *  8 +
        ( 'b' == chr || 'B' == chr ) *  2 +
        ( 'x' == chr || 'X' == chr ) * 16;

      if ( !rad ) {
        rad = 10;
      }

      u_qword_t num;
      int res = spook_str_to_uint(cur, &cur, rad, &num);

      if ( res )
        return res;

      chr = (char)( num & 0xFF );
    } break;
    }
  }

  if ( endptr ) {
    *endptr = cur;
  }

  return chr;
}

__SPOOK_PUBLIC int spook_chr_to_str (
  __SPOOK_OUT   char * str,
  __SPOOK_IN    int    chr
)
{
  static char tmp [ 5 ];

  if ( !str ) {
    str = tmp;
  }

  static char const hex [] = "0123456789ABCDEF";

  int n = 0;

  switch ( chr ) {
  case '\a'   : { str[ n++ ] = '\\'; str[ n++ ] = 'a';  } break;
  case '\b'   : { str[ n++ ] = '\\'; str[ n++ ] = 'c';  } break;
  case '\t'   : { str[ n++ ] = '\\'; str[ n++ ] = 't';  } break;
  case '\n'   : { str[ n++ ] = '\\'; str[ n++ ] = 'n';  } break;
  case '\v'   : { str[ n++ ] = '\\'; str[ n++ ] = 'v';  } break;
  case '\f'   : { str[ n++ ] = '\\'; str[ n++ ] = 'f';  } break;
  case '\r'   : { str[ n++ ] = '\\'; str[ n++ ] = 'r';  } break;
  case '\x1B' : { str[ n++ ] = '\\'; str[ n++ ] = 'e';  } break;
  case ' '    : { str[ n++ ] = '\\'; str[ n++ ] = 's';  } break;
  case '!'    : { str[ n++ ] = '\\'; str[ n++ ] = '!';  } break;
  case '?'    : { str[ n++ ] = '\\'; str[ n++ ] = '?';  } break;
  case '\''   : { str[ n++ ] = '\\'; str[ n++ ] = '\''; } break;
  case '\"'   : { str[ n++ ] = '\\'; str[ n++ ] = '\"'; } break;
  case '`'    : { str[ n++ ] = '\\'; str[ n++ ] = 'g';  } break;
  case '\x7F' : { str[ n++ ] = '\\'; str[ n++ ] = 'd';  } break;
  default     : {
    if ( ' ' < chr && chr <= '~' ) {
      str[ n++ ] = chr;
    } else {
      str[ n++ ] = '\\';
      str[ n++ ] = 'x';
      str[ n++ ] = hex[ ( chr >> 4 ) & 0xF ];
      str[ n++ ] = hex[ ( chr >> 0 ) & 0xF ];
    }
  } break;
  }

  str[ n ] = 0;
  return n;
}

__SPOOK_PUBLIC int spook_str_tok (
  __SPOOK_IN    char const * str,
  __SPOOK_IN    char const   del,
  __SPOOK_IN    int const    min_len,
  __SPOOK_IN    int const    max_len,
  __SPOOK_OUT   char *       tok_buf,
  __SPOOK_OUT   int *        tok_len
)
{
  if ( !str )
    ERRNO(EINVAL, -1);

  int len = 0;

  while ( str[ len ] && del == str[ len ]) {
    ++len;
  }

  if ( tok_len ) {
    *tok_len = len;
  }

  if ( len < min_len )
    ERRNO(EINVAL, -2);

  if ( max_len < len ) {
    len = max_len;
  }

  if ( tok_buf ) {
    /* /discard/ */ memcpy(tok_buf, str, len);
  }

  return len == max_len;
}
