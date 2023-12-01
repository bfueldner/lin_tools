headers = [
    'inc/lin/common/parser/bitrate.hpp',
    'inc/lin/common/parser/bnf.hpp',
    'inc/lin/common/parser/comment.hpp',
    'inc/lin/common/parser/signal_encoding.hpp',
    'inc/lin/common/parser/signal_init_value.hpp',

    'inc/lin/ncf/parser/diagnostic.hpp',
    'inc/lin/ncf/parser/frame.hpp',
    'inc/lin/ncf/parser/free_text.hpp',
    'inc/lin/ncf/parser/general.hpp',
    'inc/lin/ncf/parser/global.hpp',
    'inc/lin/ncf/parser/node.hpp',
    'inc/lin/ncf/parser/node_capability_file.hpp',
    'inc/lin/ncf/parser/signal.hpp',
    'inc/lin/ncf/parser/signal_encoding.hpp',
    'inc/lin/ncf/parser/status_management.hpp',

    'inc/lin/ldf/parser/frame_diagnostic.hpp',
    'inc/lin/ldf/parser/frame_event_triggered.hpp',
    'inc/lin/ldf/parser/frame_sporadic.hpp',
    'inc/lin/ldf/parser/frame_unconditional.hpp',
    'inc/lin/ldf/parser/global.hpp',
    'inc/lin/ldf/parser/lin_description_file.hpp',
    'inc/lin/ldf/parser/node_attribute.hpp',
    'inc/lin/ldf/parser/node_composition.hpp',
    'inc/lin/ldf/parser/nodes.hpp',
    'inc/lin/ldf/parser/schedule_table.hpp',
    'inc/lin/ldf/parser/signal_diagnostic.hpp',
    'inc/lin/ldf/parser/signal_encoding.hpp',
    'inc/lin/ldf/parser/signal_group.hpp',
    'inc/lin/ldf/parser/signal_representation.hpp',
    'inc/lin/ldf/parser/signal_standard.hpp',
]

lin_parser_dep = declare_dependency(
    extra_files : [
        headers,
    ],
    include_directories : include_directories('inc'),
    dependencies : [
        boost_dep,
        lin_type_dep,
    ],
)

if not meson.is_subproject()
    ncf_test_file = fs.copyfile('res/example.ncf', 'example.ncf')
    ldf13_test_file = fs.copyfile('res/example_13.ldf', 'example_13.ldf')
    ldf22_test_file = fs.copyfile('res/example_22.ldf', 'example_22.ldf')

    lin_parser_test = executable(
        'lin_parser_test',
        sources : [
            ncf_test_file,
            ldf13_test_file,
            ldf22_test_file,
            'test/main.cpp',

            'test/common/bitrate.cpp',
            'test/common/bnf.cpp',
            'test/common/comment.cpp',
            'test/common/signal_encoding.cpp',
            'test/common/signal_init_value.cpp',

            'test/ncf/diagnostic.cpp',
            'test/ncf/frame.cpp',
            'test/ncf/free_text.cpp',
            'test/ncf/general.cpp',
            'test/ncf/global.cpp',
            'test/ncf/node.cpp',
            'test/ncf/node_capability_file.cpp',
            'test/ncf/signal.cpp',
            'test/ncf/signal_encoding.cpp',
            'test/ncf/status_management.cpp',

            'test/ldf/frame_diagnostic.cpp',
            'test/ldf/frame_event_triggered.cpp',
            'test/ldf/frame_sporadic.cpp',
            'test/ldf/frame_unconditional.cpp',
            'test/ldf/global.cpp',
            'test/ldf/lin_description_file.cpp',
            'test/ldf/node_attribute.cpp',
            'test/ldf/node_composition.cpp',
            'test/ldf/nodes.cpp',
            'test/ldf/schedule_table.cpp',
            'test/ldf/signal_diagnostic.cpp',
            'test/ldf/signal_encoding.cpp',
            'test/ldf/signal_group.cpp',
            'test/ldf/signal_representation.cpp',
            'test/ldf/signal_standard.cpp',
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
endif
