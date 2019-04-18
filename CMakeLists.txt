#sets up the minimum version of cmake
cmake_minimum_required(VERSION 2.8)
#include(FindPkgConfig)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-c
        -Wall
        -Wextra
        -Winit-self
        -Wold-style-cast
        -Woverloaded-virtual
        -Wuninitialized
        -pedantic
        -pedantic-errors
        -g
)

project (saper CXX)
set(SRC_LIST
    src/main.cpp
    src/Menu.cpp

    src/ShowLayer.cpp
    src/GraphicLayer.cpp
    src/drawFieldShape.cpp

    src/ConsoleLayer.cpp
    src/MinesweeperBoard.cpp

    src/MessegesDebug.cpp

    src/GraphicControler.cpp
    )
INCLUDE_DIRECTORIES(inc)
add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif (UNIX)

# Detect and add SFML
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
