cmake_minimum_required( VERSION 3.9 )

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-utils/Modules )
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/D_CRT_SECURE_NO_WARNINGS=0>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/D_SCL_SECURE_NO_WARNINGS=0>)

project( moderncpp )

add_executable(00_arrays_classic	arrays_classic.cpp)
add_executable(00_arrays_modern 	arrays_modern.cpp)

add_executable(01_pointers_and_memory_classic	pointers_and_memory_classic.cpp)
add_executable(01_pointers_and_memory_modern 	pointers_and_memory_modern.cpp)

add_executable(02_variadic_classic	variadic_classic.cpp)
add_executable(02_variadic_modern 	variadic_modern.cpp)

add_executable(03_typedef_classic	typedef_classic.cpp)
add_executable(03_typedef_modern 	typedef_modern.cpp)

add_executable(04_auto_classic		auto_classic.cpp)
add_executable(04_auto_modern 		auto_modern.cpp)

add_executable(05_functor_classic	functor_classic.cpp)
add_executable(05_functor_modern 	functor_modern.cpp)