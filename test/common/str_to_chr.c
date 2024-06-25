# include "spook.h"
# include "main.h"

int test_str_to_chr ( void )
{
  register_signal_handler(SIGABRT, NULL);

  struct cvt_t {
    char const * str;
    char const * endptr;
    int          res;
  };

  struct cvt_t cvtv [] = {
    (struct cvt_t){   "\\e", "", 0x1B },
    (struct cvt_t){ "\\x1B", "", 0x1B }
  };

  int cvtc = (int)( sizeof(cvtv) / sizeof(cvtv[0]) );

  for ( int cvti = 0; cvti < cvtc; ++cvti ) {
    struct cvt_t * cvt = cvtv + cvti;

    char * endptr = (char *)NULL;

    int res = spook_str_to_chr(
      cvt->str, &endptr
    );

    if ( cvt->res != res )
      return -( cvti + 1 );

    if ( res < 0 )
      continue;

    if ( 0 != strcmp(endptr, cvt->endptr) )
      return -( cvti + 1 );
  }

  return 0;
}
