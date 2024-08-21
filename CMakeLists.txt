cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Vince)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the GTK package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Include GTK headers
include_directories(${GTK_INCLUDE_DIRS})

# Specify your source files
add_executable(Vince src/main.cpp)

# Link against GTK libraries
target_link_libraries(Vince ${GTK_LIBRARIES})