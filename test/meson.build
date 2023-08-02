gtest_dep = dependency('gtest', version : '>=1.10.0', main : true, required : true)
gmock_dep = dependency('gmock', version : '>=1.10.0', main : true, required : true)

fs = import('fs')

# Lexical
ncf_test_files = fs.copyfile('res/example.ncf', 'example.ncf')

lin_lexical_test = executable(
    'lin_lexical_test',
    sources : [
        ncf_test_files,
        'src/lexical/common/test_bnf.cpp',
        'src/lexical/common/test_comment.cpp',
        'src/lexical/common/test_signal_encoding.cpp',

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
    ],
    dependencies : [
        lin_lexical_dep,
        gtest_dep,
    ],
)

test(
    'lin lexical',
    lin_lexical_test,
)
