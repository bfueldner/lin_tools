project(
    'lin_tools',
    'cpp',
    version : '0.1.0',
    meson_version: '>=1.2.0',
    default_options : [
        'cpp_std=c++20',
    ]
)

boost_dep = dependency('boost', required : true)

subdir('lexical')

if not meson.is_subproject()
    subdir('test')
endif