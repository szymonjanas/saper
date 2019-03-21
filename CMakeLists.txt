#sets up the minimum version of cmake
cmake_minimum_required(VERSION 2.8)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(SFML REQUIRED graphics window system)
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

    ShowGameLayout/ShowLayer.cpp
    ShowGameLayout/GraphicLayer/src/GraphicLayer.cpp
    ShowGameLayout/GraphicLayer/src/drawFieldShape.cpp
    ShowGameLayout/ConsoleLayer/src/ConsoleLayer.cpp


    GameManagementLayout/src/FieldManagement.cpp
    GameManagementLayout/src/GameManagement.cpp

    gameLib/MessegesDebug.cpp

    src/Game.cpp
    )
INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(GameManagementLayout/inc)
INCLUDE_DIRECTORIES(ShowGameLayout/ConsoleLayer/inc)
INCLUDE_DIRECTORIES(ShowGameLayout/GraphicLayer/inc)
INCLUDE_DIRECTORIES(ShowGameLayout)
INCLUDE_DIRECTORIES(gameLib)
add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif (UNIX)

set(TEST_SRC_LIST
    tests/testMain.cpp
    tests/gameTest.cpp
    tests/fieldManagementTest.cpp
)
link_libraries(gtest)
add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)

# Detect and add SFML
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2.4.2 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(saper ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
   # target_link_libraries(saper sfml-system sfml-window sfml-graphics sfml-audio)
endif()
