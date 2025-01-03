cmake_minimum_required(VERSION 3.15...3.30)
project(GFS)

set(BUILD_SHARED_LIBS ON)
#-------------------------------------###########################--------------------------------------#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Git-from-Scratch/include")
# Here we are setting the openssl directory

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(OpenSSL REQUIRED)
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
    set(OPENSSL_INCLUDE "${OPENSSL_ROOT_DIR}/include")
    set(OPENSSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib")
else(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OPENSSL_INCLUDE "/usr/include/openssl")
    set(OPENSSL_LIBRARY_SSL "/usr/lib/x86_64-linux-gnu/libssl.so")
    set(OPENSSL_LIBRARY_CRYPTO "/usr/lib/x86_64-linux-gnu/libcrypto.so")
endif()

set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "Build zlib examples" FORCE)
#option(ZLIB_BUILD_EXAMPLES "Enable Zlib Examples" ON)

add_subdirectory(external/zlib_L)

# Executable directory
add_executable(GFS Git-from-Scratch/src/App.cpp)
set_target_properties(GFS PROPERTIES OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

target_include_directories(GFS PRIVATE ${INCLUDE_DIR})
target_include_directories(GFS PRIVATE ${OPENSSL_INCLUDE_DIR})

target_link_libraries(GFS PRIVATE zlib)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(GFS PRIVATE OpenSSL::SSL OpenSSL::Crypto)
else()
    target_link_libraries(GFS PRIVATE ${OPENSSL_LIBRARY_SSL} ${OPENSSL_LIBRARY_CRYPTO})
endif()