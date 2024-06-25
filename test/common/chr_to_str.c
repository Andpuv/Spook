# include "spook.h"
# include "main.h"

int test_chr_to_str ( void )
{
  register_signal_handler(SIGABRT, NULL);

  struct cvt_t {
    char         chr;
    char const * str;
    int          len;
  };

  struct cvt_t cvtv [] = {
    (struct cvt_t){   '\a',   "\\a", 2 },
    (struct cvt_t){ '\x1B',   "\\e", 2 },
    (struct cvt_t){ '\xFF', "\\xFF", 4 }
  };

  int cvtc = (int)( sizeof(cvtv) / sizeof(cvtv[0]) );

  for ( int cvti = 0; cvti < cvtc; ++cvti ) {
    struct cvt_t * cvt = cvtv + cvti;

    char str [ 5 ];

    int len = spook_chr_to_str(
      str, cvt->chr
    );

    if ( cvt->len != len )
      return -( cvti + 1 );

    if ( len < 0 )
      continue;

    if ( 0 != strcmp(str, cvt->str) )
      return -( cvti + 1 );
  }

  return 0;
}
