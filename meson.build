# OPS Logger Lib

project('logger', 'c', version : '4.0.0', subproject_dir: 'external')

c_args = []
link_args = []

logger_includes = include_directories('./include')

if meson.is_cross_build()
  c_args += meson.get_cross_property('cross_args')
  link_args += meson.get_cross_property('cross_link_args')
endif

if not meson.is_subproject()
  cbuff = subproject('cbuffer')
  cbuff_includes = cbuff.get_variable('cbuff_includes')
  cbuff_srcs = cbuff.get_variable('cbuff_srcs')
endif

subdir('src')
