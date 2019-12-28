project(cmake-openmp-example)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

SET(SRC_LIST
	main.cpp
)

SET(CMAKE_INCLUDE_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Need to specify appropriate compiler
SET(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

##Special openMP compilerflag is necessary to build multithreaded applications
set(CMAKE_CXX_FLAGS "-fopenmp")

message(${CMAKE_INCLUDE_CURRENT_DIR})

#Add this linker flag
include_directories(${CMAKE_INCLUDE_CURRENT_DIR})
include_directories("/usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/")

add_executable(${PROJECT_NAME} MAIN.cpp ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(${PROJECT_NAME} BEFORE PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR})
