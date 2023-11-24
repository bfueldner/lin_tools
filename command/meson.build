# Version
version_header = configure_file(
    input : 'inc/lin/common/command/version.hpp.in',
    output : 'version.hpp',
    configuration : {
        'VERSION' : meson.project_version(),
        'VERSION_MAJOR' : meson.project_version().split('.')[0],
        'VERSION_MINOR' : meson.project_version().split('.')[1],
        'VERSION_PATCH' : meson.project_version().split('.')[2],
    },
)

# NCF tool
lin_command_ncf = executable(
    'ncf_tool',
    sources : [
        version_header,
        'src/ncf/main.cpp',
        'src/ncf/function.cpp',
        'src/ncf/type_io.cpp',
        #'src/ncf/command_line.cpp',
    ],
    extra_files : [
        'inc/lin/ncf/command/type.hpp',
        'inc/lin/ncf/command/type_io.hpp',
        'inc/lin/ncf/command/main.hpp',
        'inc/lin/ncf/command/function.hpp',
        #'inc/lin/ncf/command/command_line.hpp',
    ],
    include_directories : include_directories('inc'),
    dependencies : [
        lin_parser_dep,
        lin_generator_dep,
        lin_validate_dep,
        boost_dep,
    ],
)

# LDF tool
lin_command_ldf = executable(
    'ldf_tool',
    sources : [
        version_header,
        'src/ldf/main.cpp',
        'src/ldf/function.cpp',
        'src/ldf/type_io.cpp',
        #'src/ldf/command_line.cpp',
    ],
    extra_files : [
        'inc/lin/ldf/command/type.hpp',
        'inc/lin/ldf/command/type_io.hpp',
        'inc/lin/ldf/command/main.hpp',
        'inc/lin/ldf/command/function.hpp',
        #'inc/lin/ldf/command/command_line.hpp',
    ],
    include_directories : include_directories('inc'),
    dependencies : [
        lin_parser_dep,
        lin_generator_dep,
        lin_validate_dep,
        boost_dep,
    ],
)

#lin_export_dep = declare_dependency(
##   extra_files : [
##       headers,
##   ],
#    include_directories : include_directories('inc'),
#    link_with : [
#        lin_export_library,
#    ],
#    dependencies : [
#        lin_type_dep,
#    ],
#)
