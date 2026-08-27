cmake_minimum_required(VERSION 3.13)

set(SOURCES
    src/thermal_control.cpp
    src/input_handler.cpp
    src/display_manager.cpp
    src/telemetry.cpp
    src/touch.cpp
    src/ui/src/ui/ui.c
    src/ui/src/ui/screens.c
    src/ui/src/ui/images.c
    src/ui/src/ui/styles.c
    src/ui/src/ui/actions.c
)

add_library(tejasvini ${SOURCES})
