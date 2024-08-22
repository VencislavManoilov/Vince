cmake_minimum_required(VERSION 3.10)

# Project Name
project(MyBrowser)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt (required modules: core, gui, widgets, and webengine)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets)

# Include directories
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WebEngineWidgets)