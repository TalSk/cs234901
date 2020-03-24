cmake_minimum_required(VERSION 3.10)  # CMake version check
project(competitive)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp lesson1/uva_10945.cpp lesson1/uva_11364.cpp lesson1/uva_573.cpp lesson1/uva_156.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(main ${SOURCE_FILES})