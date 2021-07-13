# OPS Logger Lib

project('logger', 'c', version : '4.0.0')

c_args = []
link_args = []

if meson.is_cross_build()
  c_args += meson.get_cross_property('cross_args')
  link_args += meson.get_cross_property('cross_link_args')
endif

logger_includes = include_directories(['./include', './external/cbuffer/include'])
logger_srcs = files(['./src/logger.c', './external/cbuffer/src/cbuffer.c'])

if not meson.is_cross_build()
  subdir('tests')
endif
