# include "spook.h"
# include "main.h"

static int aborted = 0;

static void handle_SIGABRT ( int sig )
{
  aborted = 1;
}

int test_realloc ( void )
{
  register_signal_handler(
    SIGABRT, handle_SIGABRT
  );

  void * p0 = spook_realloc(NULL, 0);

  if ( NULL != p0 )
    return -1;

  char * p1 = (char *)spook_realloc(NULL, 0x100);

  if ( aborted )
    return 1;

  /* /discard/ */ memset(p1, 0xFF, 0x100);

  if ( aborted )
    return -2;

  char p1_at_0xFF = p1[0xFF];

  char * p2 = (char *)spook_realloc(p1, 0x200);

  if ( aborted )
    return 1;

  if ( p1_at_0xFF != p2[0xFF] )
    return -3;

  p2 = (char *)spook_realloc(p2, 0);

  if ( p2 )
    return -4;

  return 0;
}
