project(
	'chopsui',
	'c',
	license: 'MIT',
	default_options: [
		'c_std=c11',
		'warning_level=2',
		'werror=true',
	],
)

add_project_arguments('-Wno-unused-parameter', language: 'c')
add_project_arguments(
	'-I@0@'.format(meson.build_root()),
	language: 'c',
)

cc = meson.get_compiler('c')
# Clang complains about some zeroed initialiser lists (= {0}), even though they
# are valid
if cc.get_id() == 'clang'
	add_project_arguments('-Wno-missing-field-initializers', language: 'c')
	add_project_arguments('-Wno-missing-braces', language: 'c')
endif

sui_inc = include_directories('include')

# TODO: This should be optional
wayland_client = dependency('wayland-client')

subdir('css')
subdir('node')
subdir('parser')
subdir('sui')
subdir('type')
subdir('util')
subdir('window')

sui_libs = [
		lib_sui_css,
		lib_sui_node,
		lib_sui_parser,
		lib_sui_sui,
		lib_sui_type,
		lib_sui_util,
		lib_sui_window,
]

lib_chopsui = library(
	'chopsui',
	link_whole: sui_libs,
	dependencies: [wayland_client],
	include_directories: sui_inc,
	install: true,
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
	libraries: lib_chopsui,
	version: '0.0.1',
	filebase: 'chopsui',
	name: 'chopsui',
	description: 'chopsui UI toolkit',
)

subdir('test')