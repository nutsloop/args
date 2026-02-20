project(
  'args',
  'cpp',
  version: '0.0.2',
  default_options: [
    'cpp_std=c++23',
    'warning_level=2',
  ],
)

cpp = meson.get_compiler('cpp')
if cpp.get_id() in ['clang', 'appleclang']
  add_project_arguments('-fexperimental-library', language: 'cpp')
  buildtype = get_option('buildtype')
  hardening_mode = '_LIBCPP_HARDENING_MODE_FAST'
  if buildtype in ['debug', 'debugoptimized']
    hardening_mode = '_LIBCPP_HARDENING_MODE_DEBUG'
  endif
  add_project_arguments(
    '-U_LIBCPP_ENABLE_ASSERTIONS',
    '-U_LIBCPP_HARDENING_MODE',
    '-D_LIBCPP_HARDENING_MODE=' + hardening_mode,
    language: 'cpp',
  )
endif

args_inc = include_directories('include')

args_sources = files(
  'src/args/args_stub.c++',
)

threads_dep = dependency('threads')

args_lib = library(
  'args',
  args_sources,
  include_directories: args_inc,
  dependencies: threads_dep,
  install: true,
)

args_dep = declare_dependency(
  link_with: args_lib,
  include_directories: args_inc,
  dependencies: threads_dep,
)

meson.override_dependency('args', args_dep)

install_subdir('include', install_dir: get_option('includedir'))

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  args_lib,
  name: 'args',
  description: 'nutsloop args parsing library',
  version: meson.project_version(),
)
