find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# add_scopy_plugin helper function to generate a plugin with the given
# target_name

function(add_scopy_plugin target_name)
    cmake_parse_arguments(
        plugin
        ""
        ""
        "SOURCES;QT_DEPENDS;SCOPY_DEPENDS;OTHER_DEPENDS"
        ${ARGN}
    )

    if(${plugin_UNPARSED_ARGUMENTS})
        message(FATAL_ERROR "add_scopy_plugin had unparsed arguments")
    endif()

    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)

    message("qt version: ${QT_VERSION_MAJOR} ")

    message("plugin name: ${target_name}")
    message("plugin sources: ${plugin_SOURCES}")
    message("plugin qt depends: ${plugin_QT_DEPENDS}")
    message("plugin scopy depends: ${plugin_SCOPY_DEPENDS}")
    message("plugin other depends: ${plugin_OTHER_DEPENDS}")

    message("==================================")
    message(${target_name} ${plugin_SOURCES} )
    add_library(${target_name} SHARED ${plugin_SOURCES})
    add_library(scopy::${target_name} ALIAS ${target_name})

    foreach(qt_lib ${plugin_QT_DEPENDS})
        message("qt lib: ${qt_lib}")
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${qt_lib} REQUIRED)
        target_link_libraries(
            ${target_name} PRIVATE Qt${QT_VERSION_MAJOR}::${qt_lib}
        )
    endforeach()

    target_link_libraries(
        ${target_name} PRIVATE ${plugin_SCOPY_DEPENDS} ${plugin_OTHER_DEPENDS}
    )

    target_link_libraries(
        ${target_name} PRIVATE Qt${QT_VERSION_MAJOR}::Core
                               Qt${QT_VERSION_MAJOR}::Widgets
    )

    # copy the plugin near scopy executable
    add_custom_command(
        TARGET ${target_name}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
                $<TARGET_FILE_DIR:scopy>/plugins
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${target_name}> $<TARGET_FILE_DIR:scopy>/plugins/
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

endfunction()

add_subdirectory(demo)
#add_subdirectory(m2k)
#add_subdirectory(m2ktoolpack)
