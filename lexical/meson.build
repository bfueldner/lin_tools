headers = [
    'inc/lin/lexical/common/bnf.hpp',

    'inc/lin/lexical/ncf/global.hpp',
    'inc/lin/lexical/ncf/general.hpp',
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
