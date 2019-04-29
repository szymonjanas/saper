#sets up the minimum version of cmake
cmake_minimum_required(VERSION 2.8)
#include(FindPkgConfig)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_INCLUDE_DIR "/home/szymon/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/szymon/SFML-2.5.1/lib")
set(SFML_DIR "/home/szymon/SFML-2.5.1/lib/cmake/SFML")
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

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
    #MAIN
    src/main.cpp
    src/Menu.cpp
    src/MenuFactory.cpp

    #MODEL
    src/MinesweeperBoardModel.cpp

    #GRAPHIC LAYER
        #GAME SETTINGS
    src/GameSFMLSettings.cpp
        #HELPFULL
    src/MousePositionConverter.cpp

    src/GraphicView.cpp
    src/FieldShapeFactory.cpp
    src/GraphicControler.cpp

    #CONSOLE LAYER
    src/ConsoleLayer.cpp
    )
INCLUDE_DIRECTORIES(inc)
set (SRC_LIST_TEST
    tests/mainTest.cpp
    tests/MousePositionConverterTest.cpp
    )
INCLUDE_DIRECTORIES(tests)


add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

add_executable(${PROJECT_NAME}-text src/mainText.cpp)
target_link_libraries(${PROJECT_NAME}-text ${PROJECT_NAME}-lib)

#TESTS
add_executable(${PROJECT_NAME}-tests ${SRC_LIST_TEST})
target_link_libraries(${PROJECT_NAME}-tests ${PROJECT_NAME}-lib)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif (UNIX)

target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_link_libraries (${PROJECT_NAME}-tests sfml-graphics sfml-window sfml-system)
target_link_libraries (${PROJECT_NAME}-text sfml-graphics sfml-window sfml-system)
