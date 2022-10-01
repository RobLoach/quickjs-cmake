cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(example)

# Dependencies
set(QUICKJS_VERSION 2021.3.27)
find_package(quickjs ${QUICKJS_VERSION} QUIET) # QUIET or REQUIRED
if (NOT quickjs_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    quickjs
    GIT_REPOSITORY https://github.com/robloach/quickjs-cmake.git
    GIT_TAG ${QUICKJS_VERSION}
  )
  FetchContent_GetProperties(quickjs)
  if (NOT quickjs_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(quickjs)
    add_subdirectory(${quickjs_SOURCE_DIR} ${quickjs_BINARY_DIR})
  endif()
endif()

# Library
add_executable(${PROJECT_NAME}
    main.c
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    quickjs
)
