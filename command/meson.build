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

# Common
lin_command_common_library = library(
    'lin_command_common',
    sources : [
        'src/common/type_io.cpp',
    ],
    extra_files : [
        'inc/lin/common/command/type.hpp',
        'inc/lin/common/command/type_io.hpp',
    ],
    include_directories : include_directories('inc'),
    install : true,
)

lin_command_common_dep = declare_dependency(
    include_directories : include_directories('inc'),
    link_with : [
        lin_command_common_library,
    ],
)

if not meson.is_subproject()
    lin_command_common_test = executable(
        'lin_command_common_test',
        sources : [
            'test/common/type_io.cpp',
        ],
        dependencies : [
            lin_command_common_dep,
            gtest_dep,
        ],
        include_directories : include_directories('inc'),
    )

    test(
        'lin command common',
        lin_command_common_test,
        is_parallel : false,
    )
endif

# NCF
lin_command_ncf_library = library(
    'lin_command_ncf',
    sources : [
        version_header,
        'src/ncf/function.cpp',
        'src/ncf/command_line.cpp',
    ],
    extra_files : [
        'inc/lin/ncf/command/function.hpp',
        'inc/lin/ncf/command/command_line.hpp',
    ],
    include_directories : include_directories('inc'),
    install : true,
    dependencies : [
        boost_dep,
        lin_generator_dep,
        lin_parser_dep,
        lin_validate_dep,
        lin_command_common_dep,
    ],
)

lin_command_ncf_dep = declare_dependency(
    include_directories : include_directories('inc'),
    link_with : [
        lin_command_ncf_library,
    ],
    dependencies : [
        boost_dep,
        lin_generator_dep,
        lin_parser_dep,
        lin_validate_dep,
        lin_command_common_dep,
    ],
)

if not meson.is_subproject()
    example_prettify_input_file = fs.copyfile('res/example_prettify_input.ncf', 'example_prettify_input.ncf')
    example_prettify_output_file = fs.copyfile('res/example_prettify_output.ncf', 'example_prettify_output.ncf')
    example_validate_file = fs.copyfile('res/example_validate.ncf', 'example_validate.ncf')

    lin_command_ncf_test = executable(
        'lin_command_ncf_test',
        sources : [
            example_prettify_input_file,
            example_prettify_output_file,
            example_validate_file,

            'test/main.cpp',

            'test/ncf/function.cpp',
            'test/ncf/command_line.cpp',
        ],
        extra_files : [
            'inc/lin/test/main.hpp',
        ],
        dependencies : [
            lin_command_ncf_dep,
            gtest_dep,
        ],
        include_directories : include_directories('inc'),
    )

    test(
        'lin command ncf',
        lin_command_ncf_test,
        is_parallel : false,
    )
endif

# NCF tool
lin_command_ncf = executable(
    'ncf_tool',
    sources : [
        'src/ncf/main.cpp',
    ],
    extra_files : [
        'inc/lin/ncf/command/main.hpp',
    ],
    include_directories : include_directories('inc'),
    install : true,
    dependencies : [
        lin_command_ncf_dep,
    ],
)

# LDF
lin_command_ldf_library = library(
    'lin_command_ldf',
    sources : [
        version_header,
        'src/ldf/function.cpp',
        'src/ldf/command_line.cpp',
    ],
    extra_files : [
        'inc/lin/ldf/command/function.hpp',
        'inc/lin/ldf/command/command_line.hpp',
    ],
    include_directories : include_directories('inc'),
    install : true,
    dependencies : [
        boost_dep,
        lin_generator_dep,
        lin_parser_dep,
        lin_validate_dep,
        lin_command_common_dep,
    ],
)

lin_command_ldf_dep = declare_dependency(
    include_directories : include_directories('inc'),
    link_with : [
        lin_command_ldf_library,
    ],
    dependencies : [
        boost_dep,
        lin_generator_dep,
        lin_parser_dep,
        lin_validate_dep,
        lin_command_common_dep,
    ],
)

if not meson.is_subproject()
    test_prettify_file = fs.copyfile('res/test_prettify.ldf', 'test_prettify.ldf')
    test_prettify_output_2_file = fs.copyfile('res/test_prettify_output_2.ldf', 'test_prettify_output_2.ldf')
    test_prettify_output_4_file = fs.copyfile('res/test_prettify_output_4.ldf', 'test_prettify_output_4.ldf')
    test_prettify_output_4_sort_file = fs.copyfile('res/test_prettify_output_4_sort.ldf', 'test_prettify_output_4_sort.ldf')
    test_validate_file = fs.copyfile('res/test_validate.ldf', 'test_validate.ldf')

    lin_command_ldf_test = executable(
        'lin_command_ldf_test',
        sources : [
            test_prettify_file,
            test_prettify_output_2_file,
            test_prettify_output_4_file,
            test_prettify_output_4_sort_file,
            test_validate_file,

            'test/main.cpp',

            #'test/ldf/function.cpp',
            'test/ldf/command_line.cpp',
        ],
        extra_files : [
            'inc/lin/test/main.hpp',
        ],
        dependencies : [
            lin_command_ldf_dep,
            gtest_dep,
        ],
        include_directories : include_directories('inc'),
    )

    test(
        'lin command ldf',
        lin_command_ldf_test,
        is_parallel : false,
    )
endif

# LDF tool
lin_command_ldf = executable(
    'ldf_tool',
    sources : [
        'src/ldf/main.cpp',
    ],
    extra_files : [
        'inc/lin/ldf/command/main.hpp',
    ],
    include_directories : include_directories('inc'),
    install : true,
    dependencies : [
        lin_command_ldf_dep,
    ],
)

# Bash completion
if host_machine.system() == 'linux'
    install_data(
        'res/lin_tools_completion',
        install_dir : '/etc/bash_completion.d',
    )
endif
