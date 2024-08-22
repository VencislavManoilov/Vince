cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Vince)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Platform-specific configurations
if(WIN32)
    set(CEF_ROOT "C:/cef_binary")  # Replace with the path to your CEF binary
elseif(UNIX AND NOT APPLE)
    set(CEF_ROOT "/path/to/cef_binary")  # Replace with the path to your CEF binary
elseif(APPLE)
    set(CEF_ROOT "/path/to/cef_binary")  # Replace with the path to your CEF binary
endif()

# Include directories and link libraries for CEF
include_directories(${CEF_ROOT}/include)
link_directories(${CEF_ROOT}/Release)

add_executable(Vince src/main.cpp)

if(WIN32)
    target_link_libraries(Vince libcef libcef_dll_wrapper)
elseif(UNIX)
    target_link_libraries(Vince ${CEF_ROOT}/Release/libcef.so)
elseif(APPLE)
    target_link_libraries(Vince ${CEF_ROOT}/Release/libcef.dylib)
endif()