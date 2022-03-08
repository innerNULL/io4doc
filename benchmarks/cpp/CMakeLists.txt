# file: CMakeLists.txt
# date: 2022-03-09


include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)


FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://${GIT_HOST}/google/benchmark.git
  GIT_TAG v1.6.1
  GIT_PROGRESS TRUE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_MakeAvailable(googlebenchmark)


include_directories(${CMAKE_SOURCE_DIR}/extensions/cpp)

add_executable(
  benchmarking 
  ${CMAKE_CURRENT_SOURCE_DIR}/benchmarking.cpp)
target_link_libraries(benchmarking benchmark::benchmark)
