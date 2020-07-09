cmake_minimum_required(VERSION 3.16)
project(PEFile_tests)

set(SRCS
        src/main.c
        src/PE.c
        )

set(CMAKE_C_FLAGS  "-I./include")
set(CMAKE_C_STANDARD 99)
add_executable(PEFile_tests ${SRCS})
target_link_libraries(PEFile_tests wsock32 ws2_32)
