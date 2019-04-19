cmake_minimum_required(VERSION 3.4)

project(Program)

#specify set of project's source files
set(SOURCE_FILES
        src/main.cpp
        )
#add following files to executable file 'Program'
add_executable(Program ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "SpaceInvaders")

#add libraries from 'Library' project
target_link_libraries(Program Library ${CURSES_LIBRARIES})

#add header files from 'include' directory of main project
target_include_directories(Program PUBLIC include)
