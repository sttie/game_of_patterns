cmake_minimum_required(VERSION 3.16)
project(game_of_patterns)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB INCLUDE_FILES
        include/commands/*.h include/commands/*.hpp
        include/controller/*.h include/controller/*.hpp
        include/game_objects/*.h include/game_objects/*.hpp
        include/graphics/*.h include/graphics/*.hpp
        include/lib/*.h include/lib/*.hpp
        include/logging/*.h include/logging/*.hpp
        include/model/*.h include/model/*.hpp
        include/snapshots/*.h include/snapshots/*.hpp
)

file(GLOB SOURCE_FILES
        src/commands/*.cpp
        src/controller/*.cpp
        src/game_objects/*.cpp
        src/graphics/*.cpp
        src/lib/*.cpp
        src/logging/*.cpp
        src/model/*.cpp
        src/snapshots/*.cpp
        main.cpp
)

add_executable(game_of_patterns
        ${INCLUDE_FILES}
        ${SOURCE_FILES}
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(game_of_patterns sfml-graphics sfml-window sfml-system Qt${QT_VERSION_MAJOR}::Widgets)