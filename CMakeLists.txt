cmake_minimum_required(VERSION 3.16)

# Project name
project(Vince LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to find Qt6
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/msvc2019_64" CACHE PATH "Path to Qt6 installation")

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui WebEngineWidgets)

# Add the executable
add_executable(Vince src/main.cpp)

# Link the Qt libraries
target_link_libraries(Vince PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::WebEngineWidgets)

# Handle Qt's automatic MOC, UIC, and RCC handling (if needed)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Handle platform-specific deployment

if (WIN32)
    # Deploy the application using windeployqt (Windows only)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")
    if (WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Vince POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:Vince>"
            COMMENT "Running windeployqt..."
        )
    endif()

elseif (APPLE)
    # macOS specific settings
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui WebEngineWidgets)
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")

    # Use macdeployqt for macOS deployment
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")
    if (MACDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Vince POST_BUILD
            COMMAND "${MACDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:Vince>"
            COMMENT "Running macdeployqt..."
        )
    endif()

elseif (UNIX)
    # Linux specific settings
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui WebEngineWidgets)
    # No specific deployment step; usually handled by packaging systems like `dpkg` or `rpm`
endif()

# Install rules for cross-platform compatibility
install(TARGETS Vince DESTINATION bin)
