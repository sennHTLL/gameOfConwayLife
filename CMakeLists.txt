cmake_minimum_required(VERSION 4.3)
project(gameOfConwayLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(gameOfConwayLife main.cpp
        CellState.h
        Grid.h
        Rules.h
        SimulationOperations.cpp
        SimulationOperations.h
        SimulationSettings.h
        Patterns.cpp
        Patterns.h
)
target_link_libraries(gameOfConwayLife
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

