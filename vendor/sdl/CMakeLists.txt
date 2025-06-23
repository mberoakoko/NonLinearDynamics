message(STATUS "\n\nFetching SDL ...\n\n")
include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-3.2.0
)

FetchContent_MakeAvailable(SDL3)
message(STATUS "\n\n Concluded Fetching SDL ...\n\n")