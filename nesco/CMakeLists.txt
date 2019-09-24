cmake_minimum_required(VERSION 3.8)

project(nesco_f746ng CXX)

add_library(libnesco
  SHARED
    core/src/Cpu.cpp
    core/src/CpuBus.cpp
    core/src/Ppu.cpp
    core/src/PpuBus.cpp
    core/src/Apu.cpp
    core/src/Ram.cpp
    core/src/Rom.cpp
    core/src/Dma.cpp
    core/src/Emu.cpp
    core/src/Mapper.cpp
    core/src/Cartridge.cpp
    hal/src/DefaultFilesystem.cpp
    hal/src/DefaultLogger.cpp
    device/Glut.cpp
  )

target_compile_definitions(libnesco PUBLIC NOMBED)

target_include_directories(libnesco
  PUBLIC ${PROJECT_SOURCE_DIR}/
  PUBLIC ${PROJECT_SOURCE_DIR}/nesco/core/include
  PUBLIC ${PROJECT_SOURCE_DIR}/nesco/hal/include
  PUBLIC ${PROJECT_SOURCE_DIR}/nesco/device
)
