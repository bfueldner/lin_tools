gtest_dep = dependency('gtest', version : '>=1.10.0', main : true, required : true)
gmock_dep = dependency('gmock', version : '>=1.10.0', main : true, required : true)

# Lexical
lin_lexical_test = executable(
    'lin_lexical_test',
    sources : [
        'src/lexical/common/test_bnf.cpp',

        'src/lexical/ncf/test_global.cpp',
        #'src/lexical/ncf/test_node.cpp',
        'src/lexical/ncf/test_general.cpp',
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
