#sets up the minimum version of cmake
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#how the project will be called

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
    src/Menu.cpp
    )
INCLUDE_DIRECTORIES(inc)
add_executable(${PROJECT_NAME} "src/main.cpp")

# Detect and add SFML
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2.4.2 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(saper ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
