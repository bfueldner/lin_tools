project(
    'lin_tools',
    'cpp',
    default_options : [
        'cpp_std=c++20',
    ],
    license : 'MIT',
    license_files : 'LICENSE',
    meson_version: '>=1.2.0',
    version : '0.4.0',
)

# Spirit V3.10 (Boost V1.78.0)
boost_dep = dependency(
    'boost',
    version : '>= 1.78.0',
    modules : ['program_options'],
    required : true
)

if not meson.is_subproject()
    gtest_dep = dependency('gtest', version : '>=1.10.0', required : true, main : true)
    gmock_dep = dependency('gmock', version : '>=1.10.0', required : true, main : true)

    fs = import('fs')
endif

subdir('type')
subdir('parser')
subdir('generator')
subdir('validate')
#subdir('export')
subdir('command')
