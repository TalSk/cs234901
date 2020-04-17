cmake_minimum_required(VERSION 3.10)  # CMake version check
project(competitive)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(LESSON1_FILES lesson1/uva_10945.cpp lesson1/uva_11364.cpp lesson1/uva_573.cpp lesson1/uva_156.cpp)
set(HW0_FILES hw0/uva_13287.cpp hw0/uva_195.cpp)
set(LESSON2_FILES lesson2/uva_10954.cpp lesson2/uva_11286.cpp lesson2/uva_11690.cpp lesson2/uva_11933.cpp lesson2/uva_E.cpp)
set(HW1_FILES hw1/uva_A.cpp hw1/uva_B.cpp)
set(MAIN main.cpp)


add_executable(hw1C hw1/uva_C.cpp)
add_executable(hw1D hw1/uva_D.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
#add_executable(lesson1e ${LESSON1_FILES})
#add_executable(hw0e ${HW0_FILES})
#add_executable(lesson2e ${LESSON2_FILES})
#add_executable(hw1e ${HW1_FILES})
#add_executable(l3A lesson3/A.cpp)
#add_executable(l3B lesson3/B.cpp)
#add_executable(l3C lesson3/C.cpp)
#add_executable(l3D lesson3/D.cpp)
