# include "spook.h"
# include "main.h"

int test_str_to_sint ( void )
{
  register_signal_handler(SIGABRT, NULL);

  struct cvt_t {
    char const * str;
    char const * endptr;
    int          rad;
    s_qword_t    num;
    int          res;
  };

  struct cvt_t cvtv [] = {
    (struct cvt_t){                     "+1", "",  0, +1,  0 },
    (struct cvt_t){                     "-1", "",  0, -1,  0 },
    (struct cvt_t){ "+0xFFFF_FFFF_FFFF_FFFF", "",  0,  0, -5 },
    (struct cvt_t){ "-0xFFFF_FFFF_FFFF_FFFF", "",  0,  0, -6 }
  };

  int cvtc = (int)( sizeof(cvtv) / sizeof(cvtv[0]) );

  for ( int cvti = 0; cvti < cvtc; ++cvti ) {
    struct cvt_t * cvt = cvtv + cvti;

    char * endptr = (char *)NULL;
    s_qword_t num = S_QWORD(0);

    int res = spook_str_to_sint(
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
