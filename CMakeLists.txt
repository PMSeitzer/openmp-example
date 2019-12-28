project(cmake-openmp-example)

cmake_minimum_required(VERSION 3.1)

#not strictly necessary, but good practice
set(CMAKE_CXX_STANDARD 11)

#Need to specify appropriate compiler
SET(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

#Special openMP compiler flag is necessary to build multithreaded applications
set(CMAKE_CXX_FLAGS "-fopenmp")

# Necessary for Qt Creator
# commenting out causes linker error:
#
# ld: library not found for -lomp
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/local/opt/llvm/lib/")

#only one source file
add_executable(${PROJECT_NAME} main.cpp)
