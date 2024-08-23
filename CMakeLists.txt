cmake_minimum_required(VERSION 3.16)

# Project name
project(Vince)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executable
add_executable(Vince src/main.cpp)

# Link libraries (assuming your libs directory is in the project root)
target_link_libraries(Vince
    ${CMAKE_SOURCE_DIR}/libs/Qt6Core.lib
    ${CMAKE_SOURCE_DIR}/libs/Qt6Gui.lib
    ${CMAKE_SOURCE_DIR}/libs/Qt6Widgets.lib
    ${CMAKE_SOURCE_DIR}/libs/Qt6WebEngineWidgets.lib
)

# Add the Qt DLLs to the output directory
add_custom_command(TARGET Vince POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/libs/Qt6Core.dll
    ${CMAKE_SOURCE_DIR}/libs/Qt6Gui.dll
    ${CMAKE_SOURCE_DIR}/libs/Qt6Widgets.dll
    ${CMAKE_SOURCE_DIR}/libs/Qt6WebEngineWidgets.dll
    $<TARGET_FILE_DIR:Vince>)