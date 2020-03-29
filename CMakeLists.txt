cmake_minimum_required(VERSION 3.10)  # CMake version check
project(competitive)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(LESSON1_FILES lesson1/uva_10945.cpp lesson1/uva_11364.cpp lesson1/uva_573.cpp lesson1/uva_156.cpp)
set(HW0_FILES hw0/uva_13287.cpp hw0/uva_195.cpp)
set(MAIN main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
# add_executable(lesson1e ${MAIN})
# add_executable(hw0e ${MAIN})