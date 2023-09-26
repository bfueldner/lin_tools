gtest_dep = dependency('gtest', version : '>=1.10.0', required : true, main : true)
gmock_dep = dependency('gmock', version : '>=1.10.0', required : true, main : true)

fs = import('fs')

# Parser
ncf_test_files = fs.copyfile('res/example.ncf', 'example.ncf')
ldf_test_files = fs.copyfile('res/example.ldf', 'example.ldf')

lin_parser_test = executable(
    'lin_parser_test',
    sources : [
        ncf_test_files,
        ldf_test_files,
        'src/main.cpp',

        'src/parser/common/test_bnf.cpp',
        'src/parser/common/test_comment.cpp',
        'src/parser/common/test_signal_encoding_type.cpp',

        'src/parser/ncf/test_global.cpp',
        'src/parser/ncf/test_node.cpp',
        'src/parser/ncf/test_general.cpp',
        'src/parser/ncf/test_diagnostic.cpp',
        'src/parser/ncf/test_frame.cpp',
        'src/parser/ncf/test_signal.cpp',
        'src/parser/ncf/test_status.cpp',
        'src/parser/ncf/test_free_text.cpp',
        'src/parser/ncf/test_node_capability_file.cpp',

        'src/parser/ldf/test_global.cpp',
        'src/parser/ldf/test_signal.cpp',
        'src/parser/ldf/test_frame.cpp',
        'src/parser/ldf/test_node.cpp',
        'src/parser/ldf/test_schedule_table.cpp',
        'src/parser/ldf/test_lin_description_file.cpp',
    ],
    extra_files : [
        'inc/lin/test/main.hpp',
    ],
    dependencies : [
        lin_parser_dep,
        gtest_dep,
    ],
    include_directories : include_directories('inc'),
)

test(
    'lin parser',
    lin_parser_test,
    is_parallel : false,
)

# Generator
lin_generator_test = executable(
    'lin_generator_test',
    sources : [
        'src/generator/common/test_indention.cpp',
        'src/generator/common/test_signal_encoding_type.cpp',

        #'src/generator/ncf/test_global.cpp',
        #'src/generator/ncf/test_node.cpp',
        #'src/generator/ncf/test_general.cpp',
        #'src/generator/ncf/test_diagnostic.cpp',
        #'src/generator/ncf/test_frame.cpp',
        #'src/generator/ncf/test_frame_properties.cpp',
        #'src/generator/ncf/test_signal.cpp',
        #'src/generator/ncf/test_signal_encoding_type.cpp',
        #'src/generator/ncf/test_status.cpp',
        #'src/generator/ncf/test_free_text.cpp',
        #'src/generator/ncf/test_node_capability_file.cpp',

        'src/generator/ldf/test_signal.cpp',
        'src/generator/ldf/test_frame.cpp',
        'src/generator/ldf/test_node.cpp',
        'src/generator/ldf/test_schedule_table.cpp',
        'src/generator/ldf/test_lin_description_file.cpp',
    ],
    extra_files : [
        #'inc/lin/test/main.hpp',
    ],
    dependencies : [
        lin_generator_dep,
        gtest_dep,
    ],
    include_directories : include_directories('inc'),
)

test(
    'lin generator',
    lin_generator_test,
    is_parallel : false,
)
