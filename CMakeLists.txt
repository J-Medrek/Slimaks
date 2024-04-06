cmake_minimum_required(VERSION 3.27)
project(Slimaks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.2\\mingw_64\\lib\\cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        Concurrent
        REQUIRED)

add_executable(Slimaks main.cpp
        Roslina.cpp
        headers/Roslina.h
        Slimak.cpp
        headers/Slimak.h
        Symulacja.cpp
        headers/Symulacja.h
        headers/SymulowanyObiekt.h
        Akwarium.cpp
        headers/Akwarium.h
        interface/WizualizatorSymulacji.cpp
        interface/WizualizatorSymulacji.h
        interface/WizualizatorSymulacji.ui
        JajoSlimaka.cpp
        headers/JajoSlimaka.h
        Zdarzenie.cpp
        headers/Zdarzenie.h
        headers/ZdarzenieLosowe.h
)

target_link_libraries(Slimaks
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        Qt6::Concurrent
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
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
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
