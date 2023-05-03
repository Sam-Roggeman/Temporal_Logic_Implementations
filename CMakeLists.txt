cmake_minimum_required(VERSION 3.20)
project(code)
file(GLOB files
        "**/*.h"
        "**/*.cpp"
)

set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
add_executable(code main.cpp ${files}  )
