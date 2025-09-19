cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

# Update this path to your Qt installation
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.2/mingw_64/lib/cmake")

# Enable Qt code generators
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(untitled ${PROJECT_SOURCES})

target_link_libraries(untitled
        PRIVATE Qt6::Core
        PRIVATE Qt6::Gui
        PRIVATE Qt6::Widgets
        PRIVATE Qt6::Multimedia
)
