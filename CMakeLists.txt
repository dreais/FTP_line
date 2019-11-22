cmake_minimum_required(VERSION 3.10)
project(ftp C)

set(CMAKE_C_STANDARD 11)

# adding pre-compiled static library
message(STATUS "Library ligeasylogs located in: ${CMAKE_SOURCE_DIR}/Libraries/libeasylogs.a")
add_library(libeasylogs STATIC IMPORTED)
set_property(TARGET libeasylogs PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Libraries/libeasylogs.a)
include_directories(${CMAKE_SOURCE_DIR}/Headers)

set(SOURCES Sources/main.c)
set(RAWCOMMANDS Sources/RawCommands/input_handle.c Sources/RawCommands/user.c)
set(FTP Sources/Sockets/connect.c Sources/Sockets/send_cmd.c)

set(C_FILES ${SOURCES} ${RAWCOMMANDS} ${FTP})
message(STATUS "Creating sources from: ${C_FILES}")
add_executable(ftp ${C_FILES})

if (UNIX)
    set(LIBS libeasylogs)
    target_compile_options(ftp PRIVATE -Wall -Wextra -g -O0)

    target_link_libraries(ftp ${LIBS})
endif (UNIX)
