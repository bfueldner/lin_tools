headers = [
    'inc/lin/lexical/common/bnf.hpp',
    'inc/lin/lexical/common/signal_encoding.hpp',
    #'inc/lin/lexical/common/error.hpp',

    'inc/lin/lexical/ncf/global.hpp',
    'inc/lin/lexical/ncf/general.hpp',
    'inc/lin/lexical/ncf/diagnostic.hpp',
    'inc/lin/lexical/ncf/frame.hpp',
    'inc/lin/lexical/ncf/frame_properties.hpp',
    'inc/lin/lexical/ncf/signal.hpp',
    'inc/lin/lexical/ncf/signal_encoding_type.hpp',
    'inc/lin/lexical/ncf/status.hpp',
    'inc/lin/lexical/ncf/free_text.hpp',
]

lin_lexical_dep = declare_dependency(
    extra_files : [
        headers,
    ],
    dependencies : [
        boost_dep,
    ],
    include_directories : include_directories('inc'),
)
