cmake_minimum_required(VERSION 3.10)

# Project Name
project(MyBrowser)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_DEBUG_FIND_PACKAGE ON)
set(CMAKE_FIND_DEBUG_MODE ON)

# Set Qt6 installation
set(Qt6_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6")

# Find Qt6 (required modules: Core, Gui, Widgets, and WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets)

# Include directories (Qt6 uses targets, so this is not required unless you have additional include directories)
include_directories(${Qt6Widgets_INCLUDE_DIRS} ${Qt6WebEngineWidgets_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

set(Qt6_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6")
set(Qt6WebEngineWidgets_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6WebEngineWidgets")
set(Qt6Quick_DIR "C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6Quick")

# Link libraries
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::WebEngineWidgets)