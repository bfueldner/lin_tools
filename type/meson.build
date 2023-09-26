headers = [
    'inc/lin/common/bnf.hpp',
    'inc/lin/common/signal_encoding_type.hpp',

    'inc/lin/ncf/global.hpp',
    'inc/lin/ncf/node.hpp',
    'inc/lin/ncf/general.hpp',
    'inc/lin/ncf/diagnostic.hpp',
    'inc/lin/ncf/frame.hpp',
    'inc/lin/ncf/frame_properties.hpp',
    'inc/lin/ncf/signal.hpp',
    'inc/lin/ncf/status.hpp',
    'inc/lin/ncf/free_text.hpp',
    'inc/lin/ncf/node_capability_file.hpp',

    'inc/lin/ldf/global.hpp',
    'inc/lin/ldf/signal.hpp',
    'inc/lin/ldf/frame.hpp',
    'inc/lin/ldf/node.hpp',
    'inc/lin/ldf/schedule_table.hpp',
    'inc/lin/ldf/lin_description_file.hpp',
]

lin_type_dep = declare_dependency(
    extra_files : [
        headers,
    ],
    include_directories : include_directories('inc'),
)
