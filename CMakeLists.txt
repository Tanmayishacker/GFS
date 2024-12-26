cmake_minimum_required(VERSION 3.20)
project(GFS)
#-------------------------------------###########################--------------------------------------#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#                           DOWNLOAD ALL SUBMODULES
find_package(GIT QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build"  ON)
    if(GIT_SUBMODULES)
        message(STATUS "Submodule update")
        execute_process( COMMAND ${GIT_EXECUTABLE} submodule update --init --recuresive 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATEL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, Please check")
        endif()
    endif()
endif()

# add_subdirectory(external/zlib)

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