# ifndef __MAIN_H
#   define __MAIN_H

#   include <string.h>
#   include <stdio.h>
#   include <stdlib.h>
#   include <signal.h>

void register_signal_handler (
  int      signal,
  void ( * handler ) ( int )
);

int test_alloc       ( void );
int test_realloc     ( void );
int test_dealloc     ( void );
int test_str_to_uint ( void );
int test_str_to_sint ( void );
int test_str_to_size ( void );
int test_str_to_chr  ( void );
int test_chr_to_str  ( void );
int test_str_tok     ( void );

# endif
