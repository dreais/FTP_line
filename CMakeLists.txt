cmake_minimum_required(VERSION 3.10)
project(ftp C)

set(CMAKE_C_STANDARD 11)

# adding pre-compiled static library
add_library(libeasylogs STATIC IMPORTED)
set_property(TARGET libeasylogs PROPERTY IMPORTED_LOCATOIN ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libeasylogs.a)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Headers)

add_executable(ftp Sources/main.c)

if (UNIX)
    set(LIBS libeasylogs)
    target_compile_options(ftp PRIVATE -Wall -Wextra -g -O0)

    target_link_libraries(ftp ${LIBS})
endif (UNIX)
