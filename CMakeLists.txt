cmake_minimum_required(VERSION 3.10)
project(Vince)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Specify the MSYS2 mingw64 environment
set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

# Find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include GTK3 headers
include_directories(${GTK3_INCLUDE_DIRS})

# Add your source files
add_executable(Vince src/main.cpp)

# Link GTK3 libraries
target_link_libraries(Vince ${GTK3_LIBRARIES})

# Add compile options
add_compile_options(${GTK3_CFLAGS_OTHER})
