# QuickJS CMake

[CMake](https://cmake.org/) definition file for [QuickJS](https://bellard.org/quickjs/).

## Usage

``` cmake
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

# Application
add_executable(MyProject main.c)
target_link_libraries(MyProject PUBLIC quickjs)
```

# License

[MIT](LICENSE)
