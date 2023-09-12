gtest_dep = dependency('gtest', version : '>=1.10.0', required : true, main : true)
gmock_dep = dependency('gmock', version : '>=1.10.0', required : true, main : true)

fs = import('fs')

# Type IO
lin_type_io_test = executable(
    'lin_type_io_test',
    sources : [
        #'src/type_io/common/test_bnf.cpp',
        'src/type_io/common/test_signal_encoding_type.cpp',

        #'src/type_io/ncf/test_global.cpp',
        #'src/type_io/ncf/test_node.cpp',
        #'src/type_io/ncf/test_general.cpp',
        #'src/type_io/ncf/test_diagnostic.cpp',
        #'src/type_io/ncf/test_frame.cpp',
        #'src/type_io/ncf/test_frame_properties.cpp',
        #'src/type_io/ncf/test_signal.cpp',
        #'src/type_io/ncf/test_signal_encoding_type.cpp',
        #'src/type_io/ncf/test_status.cpp',
        #'src/type_io/ncf/test_free_text.cpp',
        #'src/type_io/ncf/test_node_capability_file.cpp',

        #'src/type_io/ldf/test_global.cpp',
        #'src/type_io/ldf/test_node.cpp',
        'src/type_io/ldf/test_signal.cpp',
        'src/type_io/ldf/test_frame.cpp',
        'src/type_io/ldf/test_schedule_table.cpp',
        #'src/type_io/ldf/test_lin_description_file.cpp',
    ],
    extra_files : [
        #'inc/lin/test/main.hpp',
    ],
    dependencies : [
        lin_type_io_dep,
        gtest_dep,
    ],
    include_directories : include_directories('inc'),
)

# Lexical
ncf_test_files = fs.copyfile('res/example.ncf', 'example.ncf')
ldf_test_files = fs.copyfile('res/example.ldf', 'example.ldf')

lin_lexical_test = executable(
    'lin_lexical_test',
    sources : [
        ncf_test_files,
        ldf_test_files,
        'src/main.cpp',

        'src/lexical/common/test_bnf.cpp',
        'src/lexical/common/test_comment.cpp',
        'src/lexical/common/test_signal_encoding_type.cpp',

        'src/lexical/ncf/test_global.cpp',
        'src/lexical/ncf/test_node.cpp',
        'src/lexical/ncf/test_general.cpp',
        'src/lexical/ncf/test_diagnostic.cpp',
        'src/lexical/ncf/test_frame.cpp',
        'src/lexical/ncf/test_frame_properties.cpp',
        'src/lexical/ncf/test_signal.cpp',
        'src/lexical/ncf/test_signal_encoding_type.cpp',
        'src/lexical/ncf/test_status.cpp',
        'src/lexical/ncf/test_free_text.cpp',
        'src/lexical/ncf/test_node_capability_file.cpp',

        'src/lexical/ldf/test_global.cpp',
        'src/lexical/ldf/test_node.cpp',
        'src/lexical/ldf/test_signal.cpp',
        'src/lexical/ldf/test_frame.cpp',
        'src/lexical/ldf/test_schedule_table.cpp',
        'src/lexical/ldf/test_lin_description_file.cpp',
    ],
    extra_files : [
        'inc/lin/test/main.hpp',
    ],
    dependencies : [
        lin_lexical_dep,
        gtest_dep,
    ],
    include_directories : include_directories('inc'),
)

test(
    'lin lexical',
    lin_lexical_test,
)
