# include "spook.h"
# include "main.h"

static int aborted = 0;

static void handle_SIGABRT ( int sig )
{
  aborted = 1;
}

int test_alloc ( void )
{
  register_signal_handler(
    SIGABRT, handle_SIGABRT
  );

  void * p0 = spook_alloc(0);

  if ( NULL != p0 )
    return -1;

  void * p1 = spook_alloc(0x100);

  if ( aborted )
    return 1;

  memset(p1, 0, 0x100);

  if ( aborted )
    return -2;

  p1 = spook_dealloc(p1);

  if ( aborted )
    return -3;

  return 0;
}
