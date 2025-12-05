qt_add_library(nodeeditor STATIC
    node.h
    nodeeditor_viewport.h nodeeditor_viewport.cpp
    nodeeditor_scence.h nodeeditor_scence.cpp
)

target_link_libraries(nodeeditor PRIVATE Qt6::Widgets)
target_include_directories(nodeeditor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})