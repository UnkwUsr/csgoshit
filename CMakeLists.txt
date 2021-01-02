cmake_minimum_required(VERSION 3.3)
project(csgoshit)

# debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -g -std=c++14 -Wno-everything")
# release
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -std=c++14 -Wall")

# SET(CMAKE_CXX_COMPILER clang++)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")

include_directories(
    src
    )
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
# copy inject tool to build directory
configure_file(inject_tool.sh ./
                   @ONLY)

add_compile_definitions(CMD_PREFIX="hx_")
add_compile_definitions(CVAR_PREFIX="cv_")

add_library(csgoshit SHARED ${SOURCE_FILES})
target_link_libraries(csgoshit dl)

