add_executable(quickjs_example
    quickjs_example.c
)
target_link_libraries(quickjs_example PUBLIC
    quickjs
)