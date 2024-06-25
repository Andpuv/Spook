# include "spook.h"
# include "main.h"

int test_str_to_size ( void )
{
  register_signal_handler(SIGABRT, NULL);

  struct cvt_t {
    char const * str;
    char const * endptr;
    int          rad;
    u_size_t     num;
    int          res;
  };

  struct cvt_t cvtv [] = {
    (struct cvt_t){  "1K", "",  0, 1000, 0 },
    (struct cvt_t){ "1Ki", "",  0, 1024, 0 }
  };

  int cvtc = (int)( sizeof(cvtv) / sizeof(cvtv[0]) );

  for ( int cvti = 0; cvti < cvtc; ++cvti ) {
    struct cvt_t * cvt = cvtv + cvti;

    char * endptr = (char *)NULL;
    u_size_t num = U_SIZE(0);

    int res = spook_str_to_size(
      cvt->str, &endptr, cvt->rad, &num
    );

    if ( cvt->res != res )
      return -( cvti + 1 );

    if ( res )
      continue;

    if ( cvt->num != num )
      return -( cvti + 1 );

    if ( 0 != strcmp(endptr, cvt->endptr) )
      return -( cvti + 1 );
  }

  return 0;
}
