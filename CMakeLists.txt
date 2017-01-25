cmake_minimum_required(VERSION 3.6)
project(gametek)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Core)

set(SOURCE_FILES src/tools/hexview/QHexView.cpp src/tools/hexview/HexViewWindow.cpp main.cpp src/cartridge/Cartridge.cpp src/cartridge/Cartridge.hh src/Gametek.cpp src/Gametek.hh src/memory/Memory.cpp src/memory/Memory.hh src/memory/handlers/IOMemoryHandler.cpp src/memory/handlers/IOMemoryHandler.hh src/memory/handlers/ROMMemoryHandler.cpp src/memory/handlers/ROMMemoryHandler.hh src/memory/MemoryHandler.cpp src/memory/MemoryHandler.hh src/processor/Processor.cpp src/processor/Processor.hh src/memory/handlers/CommonMemoryHandler.cpp src/memory/handlers/CommonMemoryHandler.hh src/utils/EightBitRegister.cpp src/utils/EightBitRegister.hh src/utils/Color.hh src/utils/SixteenBitRegister.cpp src/utils/SixteenBitRegister.hh src/processor/Operator.hh)
add_executable(gametek ${SOURCE_FILES})

target_link_libraries(gametek Qt5Core)
target_link_libraries(gametek Qt5Gui)
target_link_libraries(gametek Qt5Widgets)

qt5_use_modules(gametek Core Widgets Gui)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/editor")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/editor")