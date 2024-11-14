cmake_minimum_required(VERSION 3.16)
project(Git-from-Scratch)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third-party/zlib-1.3.1)
# This will set the include path of the project to includes
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Git-from-Scratch/include")
# Set paths to your OpenSSL static libraries and include directory
set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/include")
set(OPENSSL_SSL_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libssl.lib")
set(OPENSSL_CRYPTO_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libcrypto.lib")

# Set TARGET_ARCH to a default value if it is not specified
if(NOT TARGET_ARCH)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(TARGET_ARCH "x64")  # Default to x64 for Linux and Windows
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(TARGET_ARCH "arm64")  # Default to arm64 for macOS (assuming Apple Silicon)
    endif()
    message(STATUS "TARGET_ARCH not specified. Defaulting to ${TARGET_ARCH}")
endif()
# Detect the generator and set configuration flags
if(CMAKE_GENERATOR STREQUAL "Ninja")
    message(STATUS "Configuring for Ninja")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNINJA_BUILD")
elseif(CMAKE_GENERATOR MATCHES "Visual Studio")
    message(STATUS "Configuring for Visual Studio")
    if(CMAKE_GENERATOR MATCHES "Visual Studio 16")
        message(STATUS "Using Visual Studio 2019 specific settings")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
    elseif(CMAKE_GENERATOR MATCHES "Visual Studio 17")
        message(STATUS "Using Visual Studio 2022 specific settings")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Zc:__cplusplus")
    endif()
endif()

# Platform-specific and user-defined architecture flags
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring for Linux with architecture ${TARGET_ARCH}")

    if(TARGET_ARCH STREQUAL "x64")
        set(ARCH_FLAGS "-m64 -march=native")
    elseif(TARGET_ARCH STREQUAL "x86")
        set(ARCH_FLAGS "-m32 -march=i686")
    elseif(TARGET_ARCH STREQUAL "arm")
        set(ARCH_FLAGS "-march=armv7-a")
    elseif(TARGET_ARCH STREQUAL "arm64")
        set(ARCH_FLAGS "-march=armv8-a")
    else()
        message(FATAL_ERROR "Unsupported architecture for Linux: ${TARGET_ARCH}")
    endif()

    set(PLATFORM_FLAGS "-Wall -Wextra -pedantic")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring for Windows with architecture ${TARGET_ARCH}")

    if(TARGET_ARCH STREQUAL "x64")
        set(ARCH_FLAGS "/arch:AVX2")
    elseif(TARGET_ARCH STREQUAL "x86")
        set(ARCH_FLAGS "/arch:SSE2")
    elseif(TARGET_ARCH STREQUAL "arm")
        set(ARCH_FLAGS "/arch:ARM")
    elseif(TARGET_ARCH STREQUAL "arm64")
        set(ARCH_FLAGS "/arch:ARM64")
    else()
        message(FATAL_ERROR "Unsupported architecture for Windows: ${TARGET_ARCH}")
    endif()

    set(PLATFORM_FLAGS "/W4")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for macOS with architecture ${TARGET_ARCH}")

    if(TARGET_ARCH STREQUAL "x64")
        set(ARCH_FLAGS "-arch x86_64")
    elseif(TARGET_ARCH STREQUAL "arm64")
        set(ARCH_FLAGS "-arch arm64 -mcpu=apple-m1")
    else()
        message(FATAL_ERROR "Unsupported architecture for macOS: ${TARGET_ARCH}")
    endif()

    set(PLATFORM_FLAGS "-Wall -Wextra -pedantic")
else()
    message(WARNING "Unknown platform, defaulting to generic flags")
    set(PLATFORM_FLAGS "-Wall -Wextra -pedantic")
endif()

# Apply platform and architecture flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PLATFORM_FLAGS} ${ARCH_FLAGS}")
# Executable directory
add_executable(Git-from-Scratch Git-from-Scratch/src/App.cpp)

target_include_directories(Git-from-Scratch PRIVATE ${INCLUDE_DIR})
target_include_directories(Git-from-Scratch PRIVATE ${OPENSSL_INCLUDE_DIR}) # Include the OpenSSL headers
target_link_libraries(Git-from-Scratch PRIVATE zlibstatic)

# Link the OpenSSL static libraries
target_link_libraries(Git-from-Scratch PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})