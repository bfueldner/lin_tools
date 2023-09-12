project(
    'lin_tools',
    'cpp',
    version : '0.2.0',
    meson_version: '>=1.2.0',
    default_options : [
        'cpp_std=c++20',
    ]
)

# Spirit V3.10 (Boost V1.78.0)
boost_dep = dependency('boost', version : '>= 1.78.0', required : true)

subdir('lexical')

if not meson.is_subproject()
    subdir('test')
endif
