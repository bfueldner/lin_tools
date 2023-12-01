gtest_dep = dependency('gtest', version : '>=1.10.0', required : true, main : true)
gmock_dep = dependency('gmock', version : '>=1.10.0', required : true, main : true)

fs = import('fs')





# Command
lin_command_test = executable(
    'lin_command_test',
    sources : [
        'src/command/common/test_signal.cpp',
    ],
    extra_files : [
        #'inc/lin/test/main.hpp',
    ],
    dependencies : [
        gtest_dep,
    ],
    include_directories : include_directories('inc'),
)

test(
    'lin command',
    lin_command_test,
    is_parallel : false,
)
