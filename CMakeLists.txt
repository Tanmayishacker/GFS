cmake_minimum_required(VERSION 3.20)
project(GFS)

set(BUILD_SHARED_LIBS ON)
#-------------------------------------###########################--------------------------------------#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(external/zlib_L)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Git-from-Scratch/include")
# Here we are setting the openssl directory
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
set(OPENSSL_INCLUDE "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib")

find_package(OpenSSL REQUIRED)

# Executable directory
add_executable(GFS Git-from-Scratch/src/App.cpp)
set_target_properties(GFS PROPERTIES OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

target_include_directories(GFS PRIVATE ${INCLUDE_DIR})
target_include_directories(GFS PRIVATE ${OPENSSL_INCLUDE_DIR})

target_link_libraries(GFS PRIVATE zlib)
target_link_libraries(GFS PRIVATE OpenSSL::SSL OpenSSL::Crypto)