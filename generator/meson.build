headers = [
    'inc/lin/common/generator/bitrate.hpp',
    'inc/lin/common/generator/indention.hpp',
    'inc/lin/common/generator/signal_encoding.hpp',
    'inc/lin/common/generator/signal_init_value.hpp',

    'inc/lin/ncf/generator/node_capability_file.hpp',
    'inc/lin/ncf/generator/node.hpp',
    'inc/lin/ncf/generator/general.hpp',
    'inc/lin/ncf/generator/diagnostic.hpp',
    'inc/lin/ncf/generator/frame.hpp',
    'inc/lin/ncf/generator/signal.hpp',
    'inc/lin/ncf/generator/signal_encoding.hpp',
    'inc/lin/ncf/generator/status_management.hpp',
    'inc/lin/ncf/generator/free_text.hpp',

    'inc/lin/ldf/generator/lin_description_file.hpp',
    'inc/lin/ldf/generator/nodes.hpp',
    'inc/lin/ldf/generator/node_attribute.hpp',
    'inc/lin/ldf/generator/node_composition.hpp',
    'inc/lin/ldf/generator/frame_unconditional.hpp',
    'inc/lin/ldf/generator/frame_diagnostic.hpp',
    'inc/lin/ldf/generator/frame_sporadic.hpp',
    'inc/lin/ldf/generator/frame_event_triggered.hpp',
    'inc/lin/ldf/generator/signal_standard.hpp',
    'inc/lin/ldf/generator/signal_diagnostic.hpp',
    'inc/lin/ldf/generator/signal_group.hpp',
    'inc/lin/ldf/generator/signal_encoding.hpp',
    'inc/lin/ldf/generator/signal_representation.hpp',
    'inc/lin/ldf/generator/schedule_table.hpp',
]

sources = [
    'src/common/bitrate.cpp',
    'src/common/indention.cpp',
    'src/common/signal_encoding.cpp',
    'src/common/signal_init_value.cpp',

    'src/ncf/node_capability_file.cpp',
    'src/ncf/general.cpp',
    'src/ncf/diagnostic.cpp',
    'src/ncf/frame.cpp',
    'src/ncf/node.cpp',
    'src/ncf/signal.cpp',
    'src/ncf/signal_encoding.cpp',
    'src/ncf/status_management.cpp',
    'src/ncf/free_text.cpp',

    'src/ldf/lin_description_file.cpp',
    'src/ldf/nodes.cpp',
    'src/ldf/node_attribute.cpp',
    'src/ldf/node_composition.cpp',
    'src/ldf/frame_unconditional.cpp',
    'src/ldf/frame_diagnostic.cpp',
    'src/ldf/frame_sporadic.cpp',
    'src/ldf/frame_event_triggered.cpp',
    'src/ldf/signal_standard.cpp',
    'src/ldf/signal_diagnostic.cpp',
    'src/ldf/signal_group.cpp',
    'src/ldf/signal_encoding.cpp',
    'src/ldf/signal_representation.cpp',
    'src/ldf/schedule_table.cpp',
]

lin_generator_library = library(
    'lin_generator',
    sources : [
        sources,
    ],
    extra_files : [
        headers,
    ],
    include_directories : include_directories('inc'),
    install : true,
    dependencies : [
        lin_type_dep,
    ],
)

lin_generator_dep = declare_dependency(
    include_directories : include_directories('inc'),
    link_with : [
        lin_generator_library,
    ],
    dependencies : [
        lin_type_dep,
    ],
)

if not meson.is_subproject()
    lin_generator_test = executable(
        'lin_generator_test',
        sources : [
            'test/common/bitrate.cpp',
            'test/common/indention.cpp',
            'test/common/signal_encoding.cpp',
            'test/common/signal_init_value.cpp',

            'test/ncf/node_capability_file.cpp',
            'test/ncf/node.cpp',
            'test/ncf/general.cpp',
            'test/ncf/diagnostic.cpp',
            'test/ncf/frame.cpp',
            'test/ncf/signal.cpp',
            'test/ncf/signal_encoding.cpp',
            'test/ncf/status_management.cpp',
            'test/ncf/free_text.cpp',

            'test/ldf/lin_description_file.cpp',
            'test/ldf/nodes.cpp',
            'test/ldf/node_attribute.cpp',
            'test/ldf/node_composition.cpp',
            'test/ldf/frame_unconditional.cpp',
            'test/ldf/frame_diagnostic.cpp',
            'test/ldf/frame_sporadic.cpp',
            'test/ldf/frame_event_triggered.cpp',
            'test/ldf/signal_standard.cpp',
            'test/ldf/signal_diagnostic.cpp',
            'test/ldf/signal_group.cpp',
            'test/ldf/signal_encoding.cpp',
            'test/ldf/signal_representation.cpp',
            'test/ldf/schedule_table.cpp',
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
endif
