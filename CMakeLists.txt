cmake_minimum_required(VERSION 3.22.1)
project(NonLinearDynamics)

set(CMAKE_CXX_STANDARD 23)

find_package(xtensor REQUIRED)

add_executable(NonLinearDynamics main.cpp)

target_include_directories(NonLinearDynamics PUBLIC ${xtensor_INCLUDE_DIRS})
target_link_libraries(NonLinearDynamics PUBLIC xtensor)