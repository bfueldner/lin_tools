headers = [
    'inc/lin/common/validate/check.hpp',
    'inc/lin/common/validate/logger.hpp',
    'inc/lin/common/validate/version.hpp',
    'inc/lin/common/validate/signal_encoding.hpp',

    'inc/lin/ncf/validate/check.hpp',
    'inc/lin/ncf/validate/node_capability_file.hpp',
    'inc/lin/ncf/validate/node.hpp',
    'inc/lin/ncf/validate/general.hpp',
    'inc/lin/ncf/validate/diagnostic.hpp',
    'inc/lin/ncf/validate/frame.hpp',
    'inc/lin/ncf/validate/signal.hpp',
    'inc/lin/ncf/validate/signal_encoding.hpp',
    'inc/lin/ncf/validate/status_management.hpp',

    'inc/lin/ldf/validate/check.hpp',
    'inc/lin/ldf/validate/lin_description_file.hpp',
    'inc/lin/ldf/validate/nodes.hpp',
    'inc/lin/ldf/validate/node_attribute.hpp',
    'inc/lin/ldf/validate/node_composition.hpp',
    'inc/lin/ldf/validate/frame.hpp',
    'inc/lin/ldf/validate/frame_event_triggered.hpp',
    'inc/lin/ldf/validate/frame_unconditional.hpp',
    'inc/lin/ldf/validate/frame_diagnostic.hpp',
    'inc/lin/ldf/validate/frame_sporadic.hpp',
    'inc/lin/ldf/validate/signal_standard.hpp',
    'inc/lin/ldf/validate/signal_diagnostic.hpp',
    'inc/lin/ldf/validate/signal_group.hpp',
    'inc/lin/ldf/validate/signal_encoding.hpp',
    'inc/lin/ldf/validate/signal_representation.hpp',
    'inc/lin/ldf/validate/schedule_table.hpp',
]

sources = [
    'src/common/logger.cpp',
    'src/common/version.cpp',
    'src/common/signal_encoding.cpp',

    'src/ncf/node_capability_file.cpp',
    'src/ncf/general.cpp',
    'src/ncf/diagnostic.cpp',
    'src/ncf/frame.cpp',
    'src/ncf/signal.cpp',
    'src/ncf/signal_encoding.cpp',
    'src/ncf/status_management.cpp',

    'src/ldf/lin_description_file.cpp',
    'src/ldf/nodes.cpp',
    'src/ldf/node_attribute.cpp',
    'src/ldf/node_composition.cpp',
    'src/ldf/frame_unconditional.cpp',
    'src/ldf/frame_diagnostic.cpp',
    'src/ldf/signal_standard.cpp',
    'src/ldf/signal_diagnostic.cpp',
    'src/ldf/signal_group.cpp',
    'src/ldf/signal_encoding.cpp',
    'src/ldf/schedule_table.cpp',
]

lin_validate_library = library(
    'lin_validate',
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

lin_validate_dep = declare_dependency(
    include_directories : include_directories('inc'),
    link_with : [
        lin_validate_library,
    ],
    dependencies : [
        lin_type_dep,
    ],
)

if not meson.is_subproject()
    lin_validate_test = executable(
        'lin_validate_test',
        sources : [
            'test/common/logger.cpp',
            'test/common/version.cpp',
            'test/common/signal_encoding.cpp',

            'test/ncf/node_capability_file.cpp',
            'test/ncf/node.cpp',
            'test/ncf/general.cpp',
            'test/ncf/diagnostic.cpp',
            'test/ncf/frame.cpp',
            'test/ncf/signal.cpp',
            'test/ncf/signal_encoding.cpp',
            'test/ncf/status_management.cpp',

            'test/ldf/lin_description_file.cpp',
            'test/ldf/nodes.cpp',
            'test/ldf/node_attribute.cpp',
            'test/ldf/node_composition.cpp',
            'test/ldf/frame_event_triggered.cpp',
            'test/ldf/frame_unconditional.cpp',
            'test/ldf/frame_diagnostic.cpp',
            'test/ldf/frame_sporadic.cpp',
            'test/ldf/signal_standard.cpp',
            'test/ldf/signal_diagnostic.cpp',
            'test/ldf/signal_group.cpp',
            'test/ldf/signal_encoding.cpp',
            'test/ldf/signal_representation.cpp',
            'test/ldf/schedule_table.cpp',
        ],
        dependencies : [
            lin_validate_dep,
            gtest_dep,
        ],
        include_directories : include_directories('inc'),
    )

    test(
        'lin validate',
        lin_validate_test,
        is_parallel : false,
    )
endif
