# include "spook.h"
# include <stdio.h>

int main ( int argc, char ** argv )
{
  (void) argc;
  (void) argv;

  printf(
    "Spook v%s has been detected.\n"
    "Spook is running on %s (%s, %s endian).\n",
    spook_get_version(),
    __SPOOK_OS, __SPOOK_ARCH, __SPOOK_ENDIAN
  );

  return 0;
}
