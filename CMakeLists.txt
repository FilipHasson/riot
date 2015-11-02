cmake_minimum_required(VERSION 3.3)
project(riot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

include_directories(include)

set(SOURCE_FILES
    include/riotCommon.h
    include/riotExec.h
    include/riotIO.h
    include/riotMap.h
    include/riotUI.h
    include/riotUnits.h
    src/riotExec.c
    src/riotIO.c
    src/riotMap.c
    src/riotUI.c
    src/riotUnits.c)

add_executable(riot ${SOURCE_FILES})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(riot ${CURSES_LIBRARIES})
