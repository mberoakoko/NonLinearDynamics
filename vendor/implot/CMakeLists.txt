# Fetch ImPlot
FetchContent_Declare(
        implot
        GIT_REPOSITORY https://github.com/epezent/implot.git
        GIT_TAG        v0.16 # Or a specific tag, or master for latest
)
FetchContent_MakeAvailable(implot)