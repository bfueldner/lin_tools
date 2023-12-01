headers = [
    'inc/lin/ncf/export/frame.hpp',
]

sources = [
    'src/ncf/frame.cpp',
]

lin_export_library = library(
    'lin_export_library',
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

lin_export_dep = declare_dependency(
#   extra_files : [
#       headers,
#   ],
    include_directories : include_directories('inc'),
    link_with : [
        lin_export_library,
    ],
    dependencies : [
        lin_type_dep,
    ],
)
