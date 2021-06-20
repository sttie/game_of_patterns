cmake_minimum_required(VERSION 3.16)
project(patterns_game)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/graphics)
include_directories(include/lib)

add_executable(patterns_game
        include/graphics/renderer.h
        include/model/cell.h
        include/model/field.h
        include/controller/field_controller.h
        include/lib/my_container.hpp
        include/logging/stream_logger.hpp
        include/logging/field_logger.h
        include/commands/command.h
        include/commands/moves.hpp
        src/graphics/renderer.cpp
        src/model/cell.cpp
        src/controller/field_controller.cpp
        src/model/field.cpp
        src/logging/field_logger.cpp
        main.cpp src/graphics/draw.cpp
        include/graphics/draw.h include/game_objects/player.h
        src/game_objects/player.cpp include/model/elements_strategies.h
        src/model/elements_strategies.cpp include/lib/raii_file.hpp
        include/logging/notifier.h include/logging/listener.h
        src/logging/notifier.cpp include/logging/file_logger.hpp
        include/commands/moves.hpp include/game_objects/enemy.hpp
        include/game_objects/behavior_types.hpp
        include/game_objects/buffs.h include/controller/states.h
        src/controller/states.cpp include/controller/states_interface.h
        include/common.h include/snapshots/snapshot.h include/snapshots/field_snapshot.h
        include/graphics/file_dialog.h include/lib/serialize.hpp src/snapshots/field_snapshot.cpp
        include/lib/type_checkers.h include/tests/snapshot_test.h
        include/lib/unit_testing.hpp include/tests/field_test.h include/tests/cell_test.h
        include/tests/raii_file_test.h include/tests/container_test.h include/tests/commands_test.h)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(patterns_game sfml-graphics sfml-window sfml-system Qt${QT_VERSION_MAJOR}::Widgets)