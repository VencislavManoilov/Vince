cmake_minimum_required(VERSION 3.16)

# Project name
project(Vince)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Path to Qt installation
set(Qt_INSTALL_DIR "${CMAKE_SOURCE_DIR}/libs")

# Set Qt directories manually (assuming headers are in 'include')
set(Qt6_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Include directories
include_directories(${Qt6_INCLUDE_DIR})

# Add the executable
add_executable(Vince src/main.cpp)

# Link libraries
target_link_libraries(Vince
    ${Qt_INSTALL_DIR}/Qt6Core.lib
    ${Qt_INSTALL_DIR}/Qt6Gui.lib
    ${Qt_INSTALL_DIR}/Qt6Widgets.lib
    ${Qt_INSTALL_DIR}/Qt6WebEngineWidgets.lib
)

# Add the Qt DLLs to the output directory
add_custom_command(TARGET Vince POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${Qt_INSTALL_DIR}/Qt6Core.dll
    ${Qt_INSTALL_DIR}/Qt6Gui.dll
    ${Qt_INSTALL_DIR}/Qt6Widgets.dll
    ${Qt_INSTALL_DIR}/Qt6WebEngineWidgets.dll
    $<TARGET_FILE_DIR:Vince>
)