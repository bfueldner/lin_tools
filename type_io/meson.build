headers = [
    'inc/lin/type_io/common/signal_encoding_type.hpp',

    #'inc/lin/type_io/ncf/global.hpp',
    #'inc/lin/type_io/ncf/node.hpp',
    #'inc/lin/type_io/ncf/general.hpp',
    #'inc/lin/type_io/ncf/diagnostic.hpp',
    #'inc/lin/type_io/ncf/frame.hpp',
    #'inc/lin/type_io/ncf/frame_properties.hpp',
    #'inc/lin/type_io/ncf/signal.hpp',
    #'inc/lin/type_io/ncf/signal_encoding_type.hpp',
    #'inc/lin/type_io/ncf/status.hpp',
    #'inc/lin/type_io/ncf/free_text.hpp',
    #'inc/lin/type_io/ncf/node_capability_file.hpp',

    #'inc/lin/type_io/ldf/global.hpp',
    #'inc/lin/type_io/ldf/node.hpp',
    'inc/lin/type_io/ldf/signal.hpp',
    'inc/lin/type_io/ldf/frame.hpp',
    'inc/lin/type_io/ldf/schedule_table.hpp',
    #'inc/lin/type_io/ldf/lin_description_file.hpp',
]

sources = [
    'src/common/signal_encoding_type.cpp',

    #'src/ldf/global.cpp',
    #'src/ldf/node.cpp',
    'src/ldf/signal.cpp',
    'src/ldf/frame.cpp',
    'src/ldf/schedule_table.cpp',
    #'src/ldf/lin_description_file.cpp',
]

lin_type_io_library = library(
    'lin_type_io_library',
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

lin_type_io_dep = declare_dependency(
#   extra_files : [
#       headers,
#   ],
    include_directories : include_directories('inc'),
    link_with : [
        lin_type_io_library,
    ],
    dependencies : [
        lin_type_dep,
    ],
)
