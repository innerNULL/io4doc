# file: CMakeLists.txt
# date: 2022-02-26


include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  pybind_pybind11
  GIT_REPOSITORY https://${GIT_HOST}/pybind/pybind11.git 
  GIT_TAG v2.9.0 
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(pybind_pybind11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

pybind11_add_module(
  keytext4py_ext_cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/pymodule.cpp)
