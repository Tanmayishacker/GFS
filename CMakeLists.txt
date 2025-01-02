cmake_minimum_required(VERSION 3.20)
project(GFS)
#-------------------------------------###########################--------------------------------------#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(external/zlib_L)

# Create a list to store the found libraries
set(FOUND_LIBRARIES)
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Git-from-Scratch/include/")
set(CRYPTOPP_INCLUDE "${CMAKE_SOURCE_DIR}/external/")
set(CRYPTOO_VSLIB "${CRYPTOPP_INCLUDE}/cryptopp/x64/Output/Release/cryptlib.lib")

# Get a list of all files in the library directory
file(GLOB LIBRARY_FILES "${CRYPTOPP_INCLUDE}/*.so" "${CRYPTOPP_INCLUDE}/*.a" "${CRYPTOPP_INCLUDE}/*.dylib")
# Iterate through the list of files
foreach(LIBRARY_FILE ${LIBRARY_FILES})
  # Extract the library name without the extension
  string(REGEX REPLACE ".so|.a|.dylib$" "" LIBRARY_NAME "${CRYPTOPP_INCLUDE}")

  # Find the library using its name
  find_library(LIBRARY_PATH ${LIBRARY_NAME} PATHS ${LIBRARY_DIR})

  # If the library is found, add it to the list
  if(LIBRARY_PATH)
    list(APPEND FOUND_LIBRARIES ${LIBRARY_PATH})
  endif()
endforeach()

include_directories(GFS PRIVATE ${INCLUDE_DIR})
include_directories(GFS PRIVATE ${CRYPTOPP_INCLUDE})

# Executable directory
add_executable(GFS Git-from-Scratch/src/App.cpp)
set_target_properties(GFS PROPERTIES OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(GFS PRIVATE "${CRYPTOO_VSLIB}")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(your_target ${FOUND_LIBRARIES})
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(your_target ${FOUND_LIBRARIES})
endif()

target_link_libraries(GFS PRIVATE zlib)