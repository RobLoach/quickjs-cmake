cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(example)

# Dependencies
include(FetchContent)
FetchContent_Declare(
    quickjscmake
    GIT_REPOSITORY https://github.com/robloach/quickjs-cmake.git
    GIT_TAG 2021.3.27
)
FetchContent_GetProperties(quickjscmake)
if (NOT quickjscmake_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(quickjscmake)
    add_subdirectory(${quickjscmake_SOURCE_DIR} ${quickjscmake_BINARY_DIR})
endif()

# Library
add_executable(${PROJECT_NAME}
    main.c
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    quickjs
)
