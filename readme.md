# Vince

## Overview

**Vince** is a C++ Browser that uses the Qt6 framework. This document provides setup and installation instructions for Windows, Linux, and macOS.

## Prerequisites

- **CMake** (version 3.16 or later)
- **Qt6** (version 6.x.x)
- A C++ compiler:
  - **Windows:** MSVC 2019 or later
  - **Linux:** GCC 9 or later
  - **macOS:** AppleClang

## Installation

### Windows

1. **Install Qt6:**
   - Download and install Qt6 from [Qt Downloads](https://www.qt.io/download-qt-installer).
   - Ensure you install the MSVC 2019 (or later) version.

2. **Set Environment Variables:**
   - Open the Command Prompt or PowerShell and set the `CMAKE_PREFIX_PATH` environment variable:
     ```cmd
     set CMAKE_PREFIX_PATH=C:\Qt\6.x.x\msvc2019_64
     ```
   - Replace `C:\Qt\6.x.x\msvc2019_64` with the actual path where Qt6 is installed.

3. **Build the Project:**
   ```cmd
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
4. **Run the Application:**
    - After building, you can find the executable in the `./build/Release` directory.

### macOS
1. **Install Qt6:**
    - Download and install Qt6 from Qt Downloads.
    - Ensure that the Qt installer is set up for macOS.
2. **Set Environment Variables:**
    - Open the Terminal and set the CMAKE_PREFIX_PATH environment variable:
      ```bash
      export CMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/clang_64
      ```
    - Replace /path/to/Qt/6.x.x/clang_64 with the actual path where Qt6 is installed.
3. **Build the Project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    ```
4. **Run the Application:**
    - After building, you can find the executable in the `./build/Release` directory.

### Linux
1. Install Qt6:
    - Depending on your distribution, you might be able to install Qt6 from your package manager. For example:
      ```bash
      sudo apt-get install qt6-base-dev qt6-webengine-dev
    - Alternatively, you can download and install Qt6 from Qt Downloads.
2. **Set Environment Variables (if necessary):**
    - If Qt6 is not installed in a standard location, set the CMAKE_PREFIX_PATH environment variable:
      ```bash
      export CMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
    - Replace /path/to/Qt/6.x.x/gcc_64 with the actual path where Qt6 is installed.
3. **Build the Project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
4. Run the Application:
    - After building, you can find the executable in the `./build/Release` directory.
  
### Key Points:
- **Environment Variables**: The instructions guide users on how to set the `CMAKE_PREFIX_PATH` environment variable, making the build process adaptable to different Qt installation paths.
- **Cross-Platform**: The `CMakeLists.txt` file is written to support Windows, Linux, and macOS, with specific deployment steps where needed.
- **User Instructions**: Clear steps are provided for each operating system to install dependencies, build the project, and run the application.
