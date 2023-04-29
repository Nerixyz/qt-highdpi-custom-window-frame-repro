cmake_minimum_required(VERSION 3.12)
project(qt-high-dpi-repro)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src)
