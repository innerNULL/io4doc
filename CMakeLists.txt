# file: CMakeLists.txt
# date: 2022-02-26


cmake_minimum_required(VERSION 3.14)
project(keytext4py-cpp-extension)

include(FetchContent)
include(ExternalProject)


option(KEYTEXT4PY_BENCHMARK "Benchmarking." FALSE)


set(CMAKE_CXX_FLAGS 
  "-fopenmp -pthread -std=c++14 -funroll-loops -O3 -march=native")


set(FETCHCONTENT_QUIET FALSE)
set(GIT_HOST "ghproxy.com/https://github.com")


add_subdirectory(extensions/cpp)


if(${KEYTEXT4PY_BENCHMARK}) 
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/cpp)
endif()
