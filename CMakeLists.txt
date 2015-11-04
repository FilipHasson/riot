cmake_minimum_required(VERSION 3.3)
project(riot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

include_directories(include)

set(SOURCE_FILES
        include/riotExec.h
        include/riotMap.h
        include/riotUI.h
        include/riotUnits.h
        src/riotMap.c
        src/riotUI.c
        src/riotUnits.c)

#add_executable(riot ${SOURCE_FILES} src/riotExec.c)
add_executable(testing ${SOURCE_FILES} src/riotTesting.c include/riotTesting.h)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
#target_link_libraries(riot ${CURSES_LIBRARIES})
target_link_libraries(testing ${CURSES_LIBRARIES})
