cmake_minimum_required(VERSION 3.13)

set(SOURCES
    src/thermal_control.cpp
    src/input_handler.cpp
    src/display_manager.cpp
    src/telemetry.cpp
)

add_library(smd_heatbed ${SOURCES})
