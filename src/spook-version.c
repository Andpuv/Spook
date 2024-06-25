# include "spook.h"

# define __(x) #x
# define _(x)  __(x)

__SPOOK_PUBLIC char const * spook_get_version (
  void
)
{
  static char const * version =
    _(__SPOOK_VERSION_MAJOR) "."
    _(__SPOOK_VERSION_MINOR) "."
    _(__SPOOK_VERSION_PATCH);

  return version;
}

# undef __
# undef _
