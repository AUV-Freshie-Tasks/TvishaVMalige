cmake_minimum_required(VERSION 3.14)
project(matrix_project)


include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.11.1
)
FetchContent_MakeAvailable(pybind11)



pybind11_add_module(matrix_module
    bindings.cpp
    lrucache.cpp
    LinearRegression.cpp
     
)

