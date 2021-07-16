cmake_minimum_required(VERSION 3.9.6)

add_scopy_plugin(
    demo
    QT_DEPENDS
    Concurrent
    SCOPY_DEPENDS
    project_options
    project_warnings
    SOURCES
    demo_plugin.cpp
    demo_tool.cpp
)
