# Fetch ImPlot
message(STATUS "Fetching Implot")
FetchContent_Declare(
        implot
        GIT_REPOSITORY https://github.com/epezent/implot.git
        GIT_TAG        v0.16 # Or a specific tag, or master for latest
)

FetchContent_MakeAvailable(implot)


set(IMPLOT_HEADERS
        ${implot_SOURCE_DIR}/implot.h
        ${implot_SOURCE_DIR}/implot_internal.h
)

set(IMPLOT_SRC
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
#        ${implot_SOURCE_DIR}/implot_demo.cpp)
)

add_library(implot ${IMPLOT_HEADERS} ${IMPLOT_SRC})
target_link_libraries(implot PUBLIC imgui)
target_include_directories(implot PUBLIC ${implot_SOURCE_DIR})
#include_directories(${implot_SOURCE_DIR})
message(STATUS "implot_SOURCE_DIR")
message(STATUS ${implot_SOURCE_DIR})