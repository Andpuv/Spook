# include "spook.h"
# include "main.h"

static int aborted = 0;

static void handle_SIGABRT ( int sig )
{
  aborted = 1;
}

int test_dealloc ( void )
{
  register_signal_handler(
    SIGABRT, handle_SIGABRT
  );

  void * p0 = spook_dealloc(NULL);

  if ( NULL != p0 )
    return -1;

  char * p1 = (char *)spook_alloc(0x100);

  if ( aborted )
    return 1;

  p1 = (char *)spook_dealloc(p1);
  
  return 0;
}
