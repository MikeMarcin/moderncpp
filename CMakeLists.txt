cmake_minimum_required( VERSION 3.9 )

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-utils/Modules )
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>)

project( moderncpp )

add_executable(00_pointers_and_memory_classic	pointers_and_memory_classic.cpp)
add_executable(00_pointers_and_memory_modern 	pointers_and_memory_modern.cpp)

add_executable(01_arrays_classic	arrays_classic.cpp)
add_executable(01_arrays_modern 	arrays_modern.cpp)