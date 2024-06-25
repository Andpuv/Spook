project('Spook', 'c',
  version         : '0.0.1',
  default_options : [
    'buildtype=debug'
  ]
)

# Configure the Spook's configuration file

config_data = configuration_data()

arch   = host_machine.cpu_family()
endian = host_machine.endian()
os     = host_machine.system()

config_data.set('ARCH_IS_X86',    arch   == 'x86'    ? 1 : 0)
config_data.set('ARCH_IS_X86_64', arch   == 'x86_64' ? 1 : 0)
config_data.set('ARCH',           arch)
config_data.set('ENDIAN_IS_LE',   endian == 'little' ? 1 : 0)
config_data.set('ENDIAN_IS_BE',   endian == 'big'    ? 1 : 0)
config_data.set('ENDIAN',         endian)
config_data.set('OS_IS_LINUX',    os     == 'linux'  ? 1 : 0)
config_data.set('OS',             os)

if meson.get_compiler('c').get_id() in [ 'gcc', 'clang' ]
  config_data.set('PRIVATE', '__attribute__((visibility("hidden")))')
  config_data.set('PROTECT', '__attribute__((visibility("default")))')
  config_data.set('PUBLIC',  '__attribute__((visibility("default")))')
else
  config_data.set('PRIVATE', '') 
  config_data.set('PROTECT', '')
  config_data.set('PUBLIC',  '')
endif

spook_config_header = configure_file(
  input         : 'src/spook-config.h.in',
  output        : 'spook-config.h',
  configuration : config_data
)

# Configure the Spook's version file

config_data = configuration_data()

version_major = '0'
version_minor = '0'
version_patch = '1'

config_data.set('VERSIONS',
  # add versions here
  '(u_dword_t []){ U_DWORD(0x00000001) }'
)
config_data.set('VERSION_MAJOR', version_major)
config_data.set('VERSION_MINOR', version_minor)
config_data.set('VERSION_PATCH', version_patch)

spook_version_header = configure_file(
  input         : 'src/spook-version.h.in',
  output        : 'spook-version.h',
  configuration : config_data
)

# Build the framework

spook_headers_dir = include_directories('src')

spook_sources = [
  'src/spook-version.c',
  'src/spook-common.c'
]

spook_lib = shared_library('spook', spook_sources,
  include_directories : spook_headers_dir,
  install             : true,
  version             : '@0@.@1@.@2@'.format(
    version_major,
    version_minor,
    version_patch
  )
)

spook_headers = [
  spook_config_header,
  spook_version_header,
  'src/spook-common.h',
  'src/spook.h'
]

# Build test executables

test_version_sources = [
  'test/version/main.c'
]

test_version_exe = executable('test-version', test_version_sources,
  include_directories : spook_headers_dir,
  link_with           : spook_lib
)

test_common_sources = [
  'test/common/main.c',
  'test/common/alloc.c',
  'test/common/realloc.c',
  'test/common/dealloc.c',
  'test/common/str_to_uint.c',
  'test/common/str_to_sint.c',
  'test/common/str_to_size.c',
  'test/common/str_to_chr.c',
  'test/common/chr_to_str.c',
  'test/common/str_tok.c'
]

test_common_exe = executable('test-common', test_common_sources,
  include_directories : spook_headers_dir,
  link_with           : spook_lib
)

# Execute tests

test('test-version', test_version_exe)
test('test-common', test_common_exe)

# Install headers

install_headers(spook_headers, subdir: 'Spook')

