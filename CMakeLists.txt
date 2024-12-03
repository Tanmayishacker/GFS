cmake_minimum_required(VERSION 3.16)
project(Git-from-Scratch VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
else()
	message("Unknown OS TYPE")
endif()

add_subdirectory(third-party/zlib-1.3.1)
# This will set the include path of the project to includes
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Git-from-Scratch/include")
# Set paths to your OpenSSL static libraries and include directory
set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/include")
set(OPENSSL_SSL_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libssl.lib")
set(OPENSSL_CRYPTO_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl/Static/libcrypto.lib")
# Executable directory
add_executable(Git-from-Scratch Git-from-Scratch/src/App.cpp)
set_target_properties(Git-from-Scratch PROPERTIES OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

target_include_directories(Git-from-Scratch PRIVATE ${INCLUDE_DIR})
target_include_directories(Git-from-Scratch PRIVATE ${OPENSSL_INCLUDE_DIR}) # Include the OpenSSL headers
target_link_libraries(Git-from-Scratch PRIVATE zlibstatic)
# Link the OpenSSL static libraries
target_link_libraries(Git-from-Scratch PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})