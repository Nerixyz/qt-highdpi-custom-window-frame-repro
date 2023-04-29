set(MAIN_EXECUTABLE xd)

set(SOURCE_FILES main.cpp)

add_executable(xd main.cpp)

target_link_libraries(xd PRIVATE Qt6::Widgets)

set_target_properties(xd PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)