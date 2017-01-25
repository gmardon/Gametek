cmake_minimum_required(VERSION 3.6)
project(editor)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Core)

set(SOURCE_FILES ../src/processor/Operator.hh ../src/cartridge/Cartridge.cpp src/main.cpp src/gui/MainWindow.cpp src/gui/MainWindow.h src/gui/Highlighter.cpp src/gui/Highlighter.h src/decompiler/Decompiler.cpp src/decompiler/Decompiler.h)
add_executable(editor ${SOURCE_FILES})

target_link_libraries(editor Qt5Core)
target_link_libraries(editor Qt5Gui)
target_link_libraries(editor Qt5Widgets)

qt5_use_modules(editor Core Widgets Gui)