set(QT_VERSION "5.14.2")
set(CLANG_VERSION "100")
set(ELFUTILS_VERSION "0.175")
set(NINJA_VERSION "1.10.0")
set(BUILD_TYPE "Release")

        set(qt_version ${QT_VERSION})

        string(REPLACE "." "" qt_version_dotless "${qt_version}")
        if (APPLE)
          set(url_os "mac_x64")
          set(qt_package_arch_suffix "clang_64")
          set(qt_dir_prefix "${qt_version}/clang_64")
          set(qt_package_suffix "-MacOS-MacOS_10_13-Clang-MacOS-MacOS_10_13-X86_64")
        endif()

        set(qt_base_url "https://download.qt.io/online/qtsdkrepository/${url_os}/desktop/qt5_${qt_version_dotless}")
        file(DOWNLOAD "${qt_base_url}/Updates.xml" ./Updates.xml SHOW_PROGRESS)

        file(READ ./Updates.xml updates_xml)
        string(REGEX MATCH "<Name>qt.qt5.*<Version>([0-9+-.]+)</Version>" updates_xml_output "${updates_xml}")
        set(qt_package_version ${CMAKE_MATCH_1})

        file(MAKE_DIRECTORY "/Users/appveyor/qt5/")

        # Save the path for other steps
        file(TO_CMAKE_PATH "/Users/appveyor/qt5/${qt_dir_prefix}" qt_dir)
        message("::set-output name=qt_dir::${qt_dir}")

        function(downloadAndExtract url archive)
          message("Downloading ${url}")
          file(DOWNLOAD "${url}" ./${archive} SHOW_PROGRESS)
          execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf ../${archive} WORKING_DIRECTORY qt5)
        endfunction()

        foreach(package qtbase qtdeclarative qttools qtsvg qtserialport qtquickcontrols qtquickcontrols2 qtgraphicaleffects qtlocation qtimageformats qttranslations)
          downloadAndExtract(
            "${qt_base_url}/qt.qt5.${qt_version_dotless}.${qt_package_arch_suffix}/${qt_package_version}${package}${qt_package_suffix}.7z"
            ${package}.7z
          )
        endforeach()

        foreach(package qtquicktimeline qtquick3d qtscript)
          downloadAndExtract(
            "${qt_base_url}/qt.qt5.${qt_version_dotless}.${package}.${qt_package_arch_suffix}/${qt_package_version}${package}${qt_package_suffix}.7z"
            ${package}.7z
          )
        endforeach()

        # uic depends on libicu56.so
#        if ("${ runner.os }" STREQUAL "Linux")
#          downloadAndExtract(
#            "${qt_base_url}/qt.qt5.${qt_version_dotless}.${qt_package_arch_suffix}/${qt_package_version}icu-linux-Rhel7.2-x64.7z"
#            icu.7z
#          )
#        endif()

        file(READ "qt5/${qt_dir_prefix}/mkspecs/qconfig.pri" qtconfig)
        string(REPLACE "Enterprise" "OpenSource" qtconfig "${qtconfig}")
        string(REPLACE "licheck.exe" "" qtconfig "${qtconfig}")
        string(REPLACE "licheck64" "" qtconfig "${qtconfig}")
        string(REPLACE "licheck_mac" "" qtconfig "${qtconfig}")
        file(WRITE "qt5/${qt_dir_prefix}/mkspecs/qconfig.pri" "${qtconfig}")
