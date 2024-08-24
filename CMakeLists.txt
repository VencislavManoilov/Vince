cmake_minimum_required(VERSION 3.16)

# Project name
project(Vince)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to find Qt6
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/msvc2019_64")

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Add the executable
add_executable(Vince src/main.cpp)

# Link the Qt libraries
target_link_libraries(Vince PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

# Add Qt include directories
target_include_directories(Vince PRIVATE ${Qt6_INCLUDE_DIRS})

# Handle Qt's automatic MOC, UIC, and RCC handling (if needed)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Copy necessary Qt DLLs to the output directory
add_custom_command(TARGET Vince POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Qt6::Core>
    $<TARGET_FILE:Qt6::Widgets>
    $<TARGET_FILE:Qt6::Gui>
    $<TARGET_FILE_DIR:Vince>
)

# If deploying on Windows, copy Qt plugins and dependencies
if (WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")
    if (WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Vince POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-quick --no-svg --no-system-d3d-compiler --no-angle "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>"
        )
    endif()
endif()