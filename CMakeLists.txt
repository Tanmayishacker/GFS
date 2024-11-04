cmake_minimum_required(VERSION 3.29)
project(Git-from-Scratch)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

#set(CMAKE_CXX_STANDARD_REQUIRED True)
# This will set the include path of the project to includes
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Git-from-Scratch/include")

add_subdirectory(third-party/zlib-1.3.1)

# Define configurations based on build type and architecture
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(CONFIG "Debug-x64")
            message(STATUS "Configuring for Debug x64 (Windows)")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(CONFIG "Debug-win32")
            message(STATUS "Configuring for Debug win32 (Windows)")
        else()
            message(FATAL_ERROR "Unsupported architecture on Windows")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")  # macOS
        if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
            set(CONFIG "Debug-arm64")
            message(STATUS "Configuring for Debug arm64 (macOS)")
        else()
            set(CONFIG "Debug-x86_64")
            message(STATUS "Configuring for Debug x86_64 (macOS)")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(CONFIG "Debug-x64")
            message(STATUS "Configuring for Debug x64 (Linux)")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(CONFIG "Debug-x86")
            message(STATUS "Configuring for Debug x86 (Linux)")
        else()
            message(FATAL_ERROR "Unsupported architecture on Linux")
        endif()
    else()
        message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(CONFIG "Release-x64")
            message(STATUS "Configuring for Release x64 (Windows)")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(CONFIG "Release-win32")
            message(STATUS "Configuring for Release win32 (Windows)")
        else()
            message(FATAL_ERROR "Unsupported architecture on Windows")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")  # macOS
        if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
            set(CONFIG "Release-arm64")
            message(STATUS "Configuring for Release arm64 (macOS)")
        else()
            set(CONFIG "Release-x86_64")
            message(STATUS "Configuring for Release x86_64 (macOS)")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(CONFIG "Release-x64")
            message(STATUS "Configuring for Release x64 (Linux)")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(CONFIG "Release-x86")
            message(STATUS "Configuring for Release x86 (Linux)")
        else()
            message(FATAL_ERROR "Unsupported architecture on Linux")
        endif()
    else()
        message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
    endif()
else()
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

# Set common compiler flags based on the configuration
# Set common compiler flags based on the configuration
if(CONFIG STREQUAL "Debug-win32" OR CONFIG STREQUAL "Debug-x64" OR CONFIG STREQUAL "Debug-arm64" OR CONFIG STREQUAL "Debug-x86_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Debug flags
elseif(CONFIG STREQUAL "Release-win32" OR CONFIG STREQUAL "Release-x64" OR CONFIG STREQUAL "Release-arm64" OR CONFIG STREQUAL "Release-x86_64")
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
target_link_options(Git-from-Scratch PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})