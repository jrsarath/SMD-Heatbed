cmake_minimum_required(VERSION 3.13)

set(SOURCES
    thermal_control.cpp
    input_handler.cpp
    display_manager.cpp
    telemetry.cpp
)

add_library(smd_heatbed ${SOURCES})
