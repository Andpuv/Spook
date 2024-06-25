# ifndef __SPOOK_COMMON_H
#   define __SPOOK_COMMON_H

__SPOOK_PUBLIC void * spook_alloc (
  __SPOOK_IN    u_size_t bytes
);

__SPOOK_PUBLIC void * spook_realloc (
  __SPOOK_IN    void *   ptr,
  __SPOOK_IN    u_size_t bytes
);

__SPOOK_PUBLIC void * spook_dealloc (
  __SPOOK_IN    void *   ptr
);

__SPOOK_PUBLIC int spook_str_to_uint (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    u_qword_t *  num
);

__SPOOK_PUBLIC int spook_str_to_sint (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    s_qword_t *  num
);

__SPOOK_PUBLIC int spook_str_to_size (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr,
  __SPOOK_IN    int          rad,
  __SPOOK_IN    u_size_t *   num
);

__SPOOK_PUBLIC int spook_str_to_chr (
  __SPOOK_IN    char const * str,
  __SPOOK_OUT   char **      endptr
);

__SPOOK_PUBLIC int spook_chr_to_str (
  __SPOOK_OUT   char * str,
  __SPOOK_IN    int    chr
);

__SPOOK_PUBLIC int spook_str_tok (
  __SPOOK_IN    char const * str,
  __SPOOK_IN    char const   del,
  __SPOOK_IN    int const    min_len,
  __SPOOK_IN    int const    max_len,
  __SPOOK_OUT   char *       tok_buf,
  __SPOOK_OUT   int *        tok_len
);

# endif
