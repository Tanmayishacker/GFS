cmake_minimum_required(VERSION 3.20)

project(GFS VERSION 0.0.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third-party)
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Git-from-Scratch/include")

set(ZLIB_INCLUDE "${THIRD_PARTY_DIR}/zlib")

set(CRYPTOPP_INCLUDE "${THIRD_PARTY_DIR}/cryptopp")
set(CRYPTOPP_LIBRARY "${THIRD_PARTY_DIR}/cryptopp/x64/Output/Release/")

# This 2 lines below will make sure that the folder is present
file(MAKE_DIRECTORY ${THIRD_PARTY_DIR}/zlib)
file(MAKE_DIRECTORY ${THIRD_PARTY_DIR}/cryptopp)

# This 2 if statements will make sure that the files are unziped
if (IS_DIRECTORY ${THIRD_PARTY_DIR}/zlib)
    # Get a list of files in the directory (excluding subdirectories)
    file(GLOB FILE_LIST "${THIRD_PARTY_DIR}/zlib/*")

    # Check if the list is empty
    list(LENGTH FILE_LIST FILE_COUNT)

    if (FILE_COUNT GREATER 0)
        message(STATUS "Directory '${THIRD_PARTY_DIR}/zlib' contains ${FILE_COUNT}/zlib file(s).")
    else()
        message(STATUS "Directory '${THIRD_PARTY_DIR}/zlib' is empty.")
        # Unzip both files into their respective directories
        if (WIN32)
            execute_process(
                COMMAND tar -xf ${THIRD_PARTY_DIR}/zlib131.zip -C ${THIRD_PARTY_DIR}/zlib
                RESULT_VARIABLE ZUNZIP_RESULT
            )
        else()
            execute_process(
                COMMAND unzip -o ${THIRD_PARTY_DIR}/zlib131.zip -d ${THIRD_PARTY_DIR}/zlib
                RESULT_VARIABLE ZUNZIP_RESULT
            )
        endif()
    endif()
endif()

if(IS_DIRECTORY ${THIRD_PARTY_DIR}/cryptopp)
    # Get a list of files in the directory (excluding subdirectories)
    file(GLOB FILE_LIST "${THIRD_PARTY_DIR}/cryptopp/*")

    # Check if the list is empty
    list(LENGTH FILE_LIST FILE_COUNT)
    if (FILE_COUNT GREATER 0)
        message(STATUS "Directory '${THIRD_PARTY_DIR}/cryptopp' contains ${FILE_COUNT} file(s).")
    else()
        message(STATUS "Directory '${THIRD_PARTY_DIR}/cryptopp' is empty.")
        if (WIN32)
            execute_process(
                COMMAND tar -xf ${THIRD_PARTY_DIR}/cryptopp890.zip -C ${THIRD_PARTY_DIR}/cryptopp
                RESULT_VARIABLE UNZIP_RESULT
            )
        else()
            execute_process(
                COMMAND unzip -o ${THIRD_PARTY_DIR}/cryptopp890.zip -d ${THIRD_PARTY_DIR}/cryptopp
                RESULT_VARIABLE UNZIP_RESULT
            )
        endif()
        if (NOT UNZIP_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to unzip zlib131.zip or cryptopp890.zip")
        endif()
    endif()
endif()

message(STATUS "Both files extracted successfully into the third-party directory.")

add_subdirectory(${THIRD_PARTY_DIR}/zlib/zlib-1.3.1)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    #execute_process(
    #    COMMAND msbuild.exe "${THIRD_PARTY_DIR}/cryptopp"
    #    /p:Configuration=Release
    #    /p:Platform=x64
    #    /t:Rebuild
    #    /p:OutDir="${PROJECT_BINARY_DIR}/output"
    #    /p:ProjectToBuild=cryptlib
    #    /v:m
    #    WORKING_DIRECTORY "${THIRD_PARTY_DIR}/cryptopp"
    #)

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    execute_process(
        COMMAND make -j$(nproc) NO_TESTS=1
    )
    set(CRYPTOPP_LIBRARY "${THIRD_PARTY_DIR}/cryptopp/")

elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
        COMMAND make -j$(nproc) NO_TESTS=1
    )
    set(CRYPTOPP_LIBRARY "${THIRD_PARTY_DIR}/cryptopp/")

else()
	message("Unknown OS TYPE")
endif()

# Executable directory
add_executable(GFS Git-from-Scratch/src/App.cpp)
set_target_properties(GFS PROPERTIES OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

target_include_directories(GFS PRIVATE ${INCLUDE_DIR})
target_include_directories(GFS PRIVATE ${ZLIB_INCLUDE})
target_include_directories(GFS PRIVATE ${CRYPTOPP_INCLUDE})

target_link_libraries(GFS PRIVATE zlibstatic zlib)
target_link_libraries(GFS PRIVATE ${CRYPTOPP_LIBRARY})