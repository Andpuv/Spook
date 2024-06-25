# include "spook.h"
# include "main.h"

int main ( int argc, char ** argv )
{
  int ( * testv [] )( void ) = {
    /* 0 */ test_alloc,
    /* 1 */ test_realloc,
    /* 2 */ test_dealloc,
    /* 3 */ test_str_to_uint,
    /* 4 */ test_str_to_sint,
    /* 5 */ test_str_to_size,
    /* 6 */ test_str_to_chr,
    /* 7 */ test_chr_to_str,
    /* 8 */ test_str_tok
  };

  int testc = (int)( sizeof(testv) / sizeof(testv[0]) );
  int res   = 0;

  for ( int testi = 0; testi < testc; ++testi ) {
    /* /discard/ */ fprintf(stderr,
      "[ ------ ] Testing %d...",
      testi
    );

    int test = testv[testi]();

    /* /discard/ */ fprintf(stderr,
      "\r[ %s ] Test %d (exit code: %d).\n",
      test ? "FAILED" : "PASSED", testi, test
    );

    if ( test < 0 ) {
      res = -1;
    } else if ( 0 < test ) {
      res = +1;
    }
  }

  if ( res < 0 )
    return EXIT_FAILURE;

  if ( 0 < res )
    return 77;

  return EXIT_SUCCESS;
}

void default_handler ( int sig )
{
  /* /discard/ */ fprintf(stderr,
    "Exiting after signal %d...",
    sig
  );

  exit(77);
}

void register_signal_handler (
  int      signum,
  void ( * handler ) ( int )
)
{
  if ( !handler ) {
    handler = default_handler;
  }

  /* /discard/ */ signal(signum, handler);
}

