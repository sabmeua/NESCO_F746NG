cmake_minimum_required(VERSION 3.8)

project(nesco_f746ng CXX)

add_executable(nesco.out main.cpp)

target_compile_options(nesco.out PUBLIC -O2 -Wall)

target_compile_features(nesco.out PUBLIC cxx_std_11)

target_compile_definitions(nesco.out PUBLIC NOMBED)

add_subdirectory(nesco)

find_package(GLUT)
find_package(OpenGL)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_include_directories(libnesco
  PUBLIC ${PROJECT_SOURCE_DIR}
  PUBLIC ${PROJECT_SOURCE_DIR}/nesco/core/include
  PUBLIC ${PROJECT_SOURCE_DIR}/nesco/hal/include
  PUBLIC ${PROJECT_SOURCE_DIR}/nesco/device
)

target_link_libraries(nesco.out PUBLIC libnesco)
target_link_libraries(nesco.out PUBLIC glut GLU GL m)
