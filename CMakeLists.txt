cmake_minimum_required(VERSION 3.16)

# Project name
project(Vince LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Allow users to set their own CMAKE_PREFIX_PATH or rely on CMake's defaults
if(NOT DEFINED CMAKE_PREFIX_PATH)
    message(STATUS "CMAKE_PREFIX_PATH is not set. CMake will try to find Qt6 in default locations.")
endif()

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui WebEngineWidgets)

# Handle Qt's automatic MOC, UIC, and RCC handling (if needed)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add the executable
add_executable(Vince src/main.cpp src/webview.cpp src/ShortcutsManager.cpp)

# Link the Qt libraries
target_link_libraries(Vince PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::WebEngineWidgets)

# Handle platform-specific deployment
if (WIN32)
    # Windows specific deployment with windeployqt
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")
    if (WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Vince POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:Vince>"
            COMMENT "Running windeployqt..."
        )
    endif()

elseif (APPLE)
    # macOS specific deployment with macdeployqt
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")
    if (MACDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Vince POST_BUILD
            COMMAND "${MACDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:Vince>"
            COMMENT "Running macdeployqt..."
        )
    endif()

elseif (UNIX)
    # Linux specific settings
    # No specific deployment step; usually handled by packaging systems like `dpkg` or `rpm`
endif()

# Install rules for cross-platform compatibility
install(TARGETS Vince DESTINATION bin)
