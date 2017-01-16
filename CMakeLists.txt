cmake_minimum_required(VERSION 3.6)
project(gametek)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp src/cartridge/Cartridge.cpp src/cartridge/Cartridge.hh src/Gametek.cpp src/Gametek.hh src/memory/Memory.cpp src/memory/Memory.hh src/memory/handlers/IOMemoryHandler.cpp src/memory/handlers/IOMemoryHandler.hh src/memory/handlers/ROMMemoryHandler.cpp src/memory/handlers/ROMMemoryHandler.hh src/memory/MemoryHandler.cpp src/memory/MemoryHandler.hh src/processor/Processor.cpp src/processor/Processor.hh src/memory/handlers/CommonMemoryHandler.cpp src/memory/handlers/CommonMemoryHandler.hh src/utils/EightBitRegister.cpp src/utils/EightBitRegister.hh src/utils/Color.hh src/utils/SixteenBitRegister.cpp src/utils/SixteenBitRegister.hh src/processor/Operator.hh)
add_executable(gametek ${SOURCE_FILES})