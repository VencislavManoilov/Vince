cmake_minimum_required(VERSION 3.16)  # Update to at least 3.16 for Qt6 support

# Project name
project(Vince)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the required Qt packages
set(Qt6_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6")
set(Qt6CoreTools_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6CoreTools")
set(Qt6WidgetsTools_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6WidgetsTools")
set(Qt6Widgets_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6Widgets")

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

# Add the executable
add_executable(Vince src/main.cpp)

# Link the Qt libraries
target_link_libraries(Vince Qt6::Widgets Qt6::WebEngineWidgets)