find_package(benchmark REQUIRED)

add_executable(bench 
    bm_strmanip.cpp
    main.cpp
)
target_link_libraries(bench 
    PRIVATE steg benchmark::benchmark
)
