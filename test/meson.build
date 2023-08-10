gtest_dep = dependency('gtest', version : '>=1.10.0', required : true)
gmock_dep = dependency('gmock', version : '>=1.10.0', required : true)

fs = import('fs')

# Lexical
ncf_test_files = fs.copyfile('res/example.ncf', 'example.ncf')

lin_lexical_test = executable(
    'lin_lexical_test',
    sources : [
        ncf_test_files,
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
        #'src/lexical/ldf/test_node_attributes.cpp',
        'src/lexical/ldf/test_signal.cpp',
        'src/lexical/ldf/test_frame.cpp',
        'src/lexical/ldf/test_schedule_table.cpp',
        'src/lexical/ldf/test_signal_encoding_type.cpp',
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
