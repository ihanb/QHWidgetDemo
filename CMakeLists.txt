cmake_minimum_required(VERSION 3.24)
project(HWidgetDemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB SRC_LIST "src/*")
file(GLOB SRC_TABLEVIEW "src/tableview/*")
file(GLOB SRC_IMAGEWIDGET "src/imagewidget/*")
file(GLOB SRC_TREEVIEW" src/treeview/*")
file(GLOB SRC_FRAMELESSWIDGET" src/framelesswidget/*")
list(APPEND ALL_SRC_LIST ${SRC_LIST})
list(APPEND ALL_SRC_LIST ${SRC_TABLEVIEW})
list(APPEND ALL_SRC_LIST ${SRC_IMAGEWIDGET})
list(APPEND ALL_SRC_LIST ${SRC_TREEVIEW})
list(APPEND ALL_SRC_LIST ${SRC_FRAMELESSWIDGET})

add_executable(${PROJECT_NAME} ${ALL_SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE
        src/tableview
        src/imagewidget
        src/treeview
        src/framelesswidget
        )

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()