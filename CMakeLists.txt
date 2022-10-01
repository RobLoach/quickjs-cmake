cmake_minimum_required(VERSION 3.11)
project(quickjs
    DESCRIPTION "QuickJS: A small and embeddable Javascript engine."
    HOMEPAGE_URL "https://bellard.org/quickjs/"
    VERSION 2021.3.27
    LANGUAGES C
)

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(QUICKJS_IS_MAIN TRUE)
else()
    set(QUICKJS_IS_MAIN FALSE)
endif()
option(QUICKJS_BUILD_EXAMPLE "QuickJS Example" ${QUICKJS_IS_MAIN})

# QuickJS
set(QUICKJS_COMMIT b5e62895c619d4ffc75c9d822c8d85f1ece77e5b)
include(FetchContent)
FetchContent_Declare(
   quickjs
   GIT_REPOSITORY https://github.com/bellard/quickjs.git
   GIT_TAG ${QUICKJS_COMMIT}
)
FetchContent_MakeAvailable(quickjs)

# Dependencies
include(CheckLibraryExists)

# Dependency: Math
check_library_exists(m cos "" HAVE_LIB_M)
if (HAVE_LIB_M)
    set(QUICKJS_DEPENDENCIES ${EXTRA_LIBS} m)
endif()

# Sources
set(QUICKJS_SRC
    ${quickjs_SOURCE_DIR}/quickjs.c
    ${quickjs_SOURCE_DIR}/libregexp.c
    ${quickjs_SOURCE_DIR}/libunicode.c
    ${quickjs_SOURCE_DIR}/cutils.c
    #${quickjs_SOURCE_DIR}/quickjs-libc.c
    ${quickjs_SOURCE_DIR}/libbf.c
)

# Library
add_library(quickjs STATIC ${QUICKJS_SRC})
target_include_directories(quickjs PUBLIC ${quickjs_SOURCE_DIR})
target_compile_definitions(quickjs PUBLIC CONFIG_VERSION="${PROJECT_VERSION}")
target_link_libraries(quickjs PUBLIC ${QUICKJS_DEPENDENCIES})

# Examples
if (QUICKJS_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
