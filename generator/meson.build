headers = [
    'inc/lin/common/generator/indention.hpp',
    'inc/lin/common/generator/signal_encoding_type.hpp',

    #'inc/lin/ncf/generator/global.hpp',
    'inc/lin/ncf/generator/diagnostic.hpp',
    'inc/lin/ncf/generator/frame.hpp',
    'inc/lin/ncf/generator/free_text.hpp',
    'inc/lin/ncf/generator/general.hpp',
    'inc/lin/ncf/generator/node.hpp',
    'inc/lin/ncf/generator/node_capability_file.hpp',
    'inc/lin/ncf/generator/signal.hpp',
    'inc/lin/ncf/generator/status.hpp',

    'inc/lin/ldf/generator/frame.hpp',
    'inc/lin/ldf/generator/lin_description_file.hpp',
    'inc/lin/ldf/generator/node.hpp',
    'inc/lin/ldf/generator/schedule_table.hpp',
    'inc/lin/ldf/generator/signal.hpp',
]

sources = [
    'src/common/indention.cpp',
    'src/common/signal_encoding_type.cpp',

    'src/ncf/diagnostic.cpp',
    'src/ncf/frame.cpp',
    'src/ncf/free_text.cpp',
    'src/ncf/general.cpp',
    'src/ncf/node.cpp',
    'src/ncf/node_capability_file.cpp',
    'src/ncf/signal.cpp',
    'src/ncf/status.cpp',

    'src/ldf/frame.cpp',
    'src/ldf/lin_description_file.cpp',
    'src/ldf/node.cpp',
    'src/ldf/schedule_table.cpp',
    'src/ldf/signal.cpp',
]

lin_generator_library = library(
    'lin_generator_library',
    sources : [
        sources,
    ],
    extra_files : [
        headers,
    ],
    include_directories : include_directories('inc'),
    dependencies : [
        lin_type_dep,
    ],
)

lin_generator_dep = declare_dependency(
#   extra_files : [
#       headers,
#   ],
    include_directories : include_directories('inc'),
    link_with : [
        lin_generator_library,
    ],
    dependencies : [
        lin_type_dep,
    ],
)
