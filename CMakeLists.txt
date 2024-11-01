cmake_minimum_required(VERSION 3.29)
project(Git-from-Scratch)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

#set(CMAKE_CXX_STANDARD_REQUIRED True)
# This will set the include path of the project to includes
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(third-party/zlib-1.3.1)

# Set paths to your OpenSSL static libraries and include directory
set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/include")
set(OPENSSL_SSL_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libssl.lib")
set(OPENSSL_CRYPTO_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libcrypto.lib")

# Executable directory
add_executable(Git-from-Scratch src/App.cpp)

target_include_directories(Git-from-Scratch PRIVATE ${INCLUDE_DIR})
target_include_directories(Git-from-Scratch PRIVATE ${OPENSSL_INCLUDE_DIR}) # Include the OpenSSL headers
target_link_libraries(Git-from-Scratch PRIVATE zlib)

# Link the OpenSSL static libraries
target_link_options(Git-from-Scratch PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})