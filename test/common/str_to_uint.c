# include "spook.h"
# include "main.h"

int test_str_to_uint ( void )
{
  register_signal_handler(SIGABRT, NULL);

  struct cvt_t {
    char const * str;
    char const * endptr;
    int          rad;
    u_qword_t    num;
    int          res;
  };

  struct cvt_t cvtv [] = {
    (struct cvt_t){        "0x_1",       "",  0, 0x00, -3 },
    (struct cvt_t){        "0x1_",       "",  0, 0x00, -4 },
    (struct cvt_t){ "0b1111_1111",       "",  0, 0xFF,  0 },
    (struct cvt_t){ "0B0000_1010",       "",  0, 0x0A,  0 },
    (struct cvt_t){ "0b0007_0000", "7_0000",  0, 0x00,  0 },
    (struct cvt_t){        "0o77",       "",  0, 0x3F,  0 },
    (struct cvt_t){        "0O77",       "",  0, 0x3F,  0 },
    (struct cvt_t){         "077",       "",  0, 0x3F,  0 },
    (struct cvt_t){         "078",      "8",  0, 0x07,  0 },
    (struct cvt_t){         "128",       "",  0, 0x80,  0 },
    (struct cvt_t){         "12A",      "A",  0, 0x0C,  0 },
    (struct cvt_t){        "0xFF",       "",  0, 0xFF,  0 },
    (struct cvt_t){        "0XFF",       "",  0, 0xFF,  0 },
    (struct cvt_t){        "0XFG",      "G",  0, 0x0F,  0 },
    (struct cvt_t){        "3r10",       "",  0, 0x03,  0 },
    (struct cvt_t){        "3R10",       "",  0, 0x03,  0 },
    (struct cvt_t){        "3r13",      "3",  0, 0x01,  0 },
    (struct cvt_t){        "1111",       "",  2, 0x0F,  0 },
    (struct cvt_t){           "F",       "", 16, 0x0F,  0 },
    (struct cvt_t){           "X",       "", 37, 0x00, -2 }
  };

  int cvtc = (int)( sizeof(cvtv) / sizeof(cvtv[0]) );

  for ( int cvti = 0; cvti < cvtc; ++cvti ) {
    struct cvt_t * cvt = cvtv + cvti;

    char * endptr = (char *)NULL;
    u_qword_t num = U_QWORD(0);

    int res = spook_str_to_uint(
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
