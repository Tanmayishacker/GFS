cmake_minimum_required(VERSION 3.16)
project(Git-from-Scratch)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

#set(CMAKE_CXX_STANDARD_REQUIRED True)
# This will set the include path of the project to includes
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Git-from-Scratch/include")

add_subdirectory(third-party/zlib-1.3.1)

# User-defined variables for architecture and tool
if(NOT DEFINED TARGET_ARCH)
    set(TARGET_ARCH "x64")  # Default architecture
endif()

if(NOT DEFINED BUILD_TOOL)
    set(BUILD_TOOL "default")  # Default to whatever CMake generator is used
endif()

message(STATUS "Building for architecture: ${TARGET_ARCH}")
message(STATUS "Using build tool: ${BUILD_TOOL}")

# Define configurations based on build type and architecture
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(TARGET_ARCH STREQUAL "win32")
        set(CONFIG "Debug-win32")
        message(STATUS "Configuring for Debug win32")
    elseif(TARGET_ARCH STREQUAL "x64")
        set(CONFIG "Debug-x64")
        message(STATUS "Configuring for Debug x64")
    elseif(TARGET_ARCH STREQUAL "arm64" AND CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CONFIG "Debug-arm64")
        message(STATUS "Configuring for Debug arm64 (macOS)")
    elseif(TARGET_ARCH STREQUAL "x86_64" AND CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CONFIG "Debug-x86_64")
        message(STATUS "Configuring for Debug x86_64 (macOS)")
    elseif(TARGET_ARCH STREQUAL "x86" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CONFIG "Debug-x86")
        message(STATUS "Configuring for Debug x86 (Linux)")
    elseif(TARGET_ARCH STREQUAL "x64" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CONFIG "Debug-x64")
        message(STATUS "Configuring for Debug x64 (Linux)")
    else()
        message(FATAL_ERROR "Unsupported architecture or build type: ${TARGET_ARCH} for ${CMAKE_BUILD_TYPE}")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(TARGET_ARCH STREQUAL "win32")
        set(CONFIG "Release-win32")
        message(STATUS "Configuring for Release win32")
    elseif(TARGET_ARCH STREQUAL "x64")
        set(CONFIG "Release-x64")
        message(STATUS "Configuring for Release x64")
    elseif(TARGET_ARCH STREQUAL "arm64" AND CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CONFIG "Release-arm64")
        message(STATUS "Configuring for Release arm64 (macOS)")
    elseif(TARGET_ARCH STREQUAL "x86_64" AND CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CONFIG "Release-x86_64")
        message(STATUS "Configuring for Release x86_64 (macOS)")
    elseif(TARGET_ARCH STREQUAL "x86" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CONFIG "Release-x86")
        message(STATUS "Configuring for Release x86 (Linux)")
    elseif(TARGET_ARCH STREQUAL "x64" AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CONFIG "Release-x64")
        message(STATUS "Configuring for Release x64 (Linux)")
    else()
        message(FATAL_ERROR "Unsupported architecture or build type: ${TARGET_ARCH} for ${CMAKE_BUILD_TYPE}")
    endif()
else()
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

# Set common compiler flags based on the configuration
if(CONFIG MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Debug flags
elseif(CONFIG MATCHES "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")  # Release flags
endif()

# Set paths to your OpenSSL static libraries and include directory
set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/include")
set(OPENSSL_SSL_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libssl.lib")
set(OPENSSL_CRYPTO_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libcrypto.lib")

# Executable directory
add_executable(Git-from-Scratch Git-from-Scratch/src/App.cpp)

target_include_directories(Git-from-Scratch PRIVATE ${INCLUDE_DIR})
target_include_directories(Git-from-Scratch PRIVATE ${OPENSSL_INCLUDE_DIR}) # Include the OpenSSL headers
target_link_libraries(Git-from-Scratch PRIVATE zlib)

# Link the OpenSSL static libraries
target_link_libraries(Git-from-Scratch PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})