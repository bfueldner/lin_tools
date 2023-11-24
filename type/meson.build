headers = [
    'inc/lin/common/bnf.hpp',
    'inc/lin/common/bitrate.hpp',
    'inc/lin/common/signal_encoding.hpp',
    'inc/lin/common/signal_init_value.hpp',

    'inc/lin/ncf/node_capability_file.hpp',
    'inc/lin/ncf/node.hpp',
    'inc/lin/ncf/general.hpp',
    'inc/lin/ncf/diagnostic.hpp',
    'inc/lin/ncf/frame.hpp',
    'inc/lin/ncf/signal.hpp',
    'inc/lin/ncf/signal_encoding.hpp',
    'inc/lin/ncf/status_management.hpp',
    'inc/lin/ncf/free_text.hpp',

    'inc/lin/ldf/lin_description_file.hpp',
    'inc/lin/ldf/signal_standard.hpp',
    'inc/lin/ldf/signal_diagnostic.hpp',
    'inc/lin/ldf/signal_group.hpp',
    'inc/lin/ldf/signal_encoding.hpp',
    'inc/lin/ldf/signal_representation.hpp',
    'inc/lin/ldf/frame_unconditional.hpp',
    'inc/lin/ldf/frame_diagnostic.hpp',
    'inc/lin/ldf/frame_sporadic.hpp',
    'inc/lin/ldf/frame_event_triggered.hpp',
    'inc/lin/ldf/nodes.hpp',
    'inc/lin/ldf/node_attribute.hpp',
    'inc/lin/ldf/node_composition.hpp',
    'inc/lin/ldf/schedule_table.hpp',
]

lin_type_dep = declare_dependency(
    extra_files : [
        headers,
    ],
    include_directories : include_directories('inc'),
)
