cmake_minimum_required(VERSION 3.22.1)
project(NonLinearDynamics)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

find_package(xtensor REQUIRED)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        # docking-latest
        GIT_TAG v1.91.8
)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/sdl)
add_subdirectory(vendor/implot)

add_executable(NonLinearDynamics main.cpp
        src/systems/system_base.hpp
        src/systems/concrete_systems.hpp
        src/integrators/multistep_integrator.hpp
        src/threading/threading_ops.hpp
        src/sqp_solvers/newton_method.hpp
        src/utils/util.hpp
        src/gui_dashboard/dashboard.hpp
        src/gui_dashboard/dashboard_ops/app_primitives.hpp)

target_link_libraries(NonLinearDynamics PUBLIC
        xtensor
        SDL3::SDL3
#        implot
        imgui
)
target_link_libraries(NonLinearDynamics PUBLIC implot)

target_include_directories(NonLinearDynamics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${xtensor_INCLUDE_DIRS}
        ${implot_SOURCE_DIR}
)