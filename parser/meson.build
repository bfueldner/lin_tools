headers = [
    'inc/lin/common/parser/bnf.hpp',
    'inc/lin/common/parser/comment.hpp',
    'inc/lin/common/parser/signal_encoding_type.hpp',

    'inc/lin/ncf/parser/global.hpp',
    'inc/lin/ncf/parser/node.hpp',
    'inc/lin/ncf/parser/general.hpp',
    'inc/lin/ncf/parser/diagnostic.hpp',
    'inc/lin/ncf/parser/frame.hpp',
    'inc/lin/ncf/parser/signal.hpp',
    'inc/lin/ncf/parser/status.hpp',
    'inc/lin/ncf/parser/free_text.hpp',
    'inc/lin/ncf/parser/node_capability_file.hpp',

    'inc/lin/ldf/parser/global.hpp',
    'inc/lin/ldf/parser/signal.hpp',
    'inc/lin/ldf/parser/frame.hpp',
    'inc/lin/ldf/parser/node.hpp',
    'inc/lin/ldf/parser/schedule_table.hpp',
    'inc/lin/ldf/parser/lin_description_file.hpp',
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
